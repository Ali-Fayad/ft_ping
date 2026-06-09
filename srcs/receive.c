/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:00:57 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 15:01:08 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_ping.h"

static const char	*verbose_message(struct icmp *icmp_hdr)
{
	if (icmp_hdr->icmp_type == ICMP_TIMXCEED)
		return (VERBOSE_TIME_EXCEEDED);
	if (icmp_hdr->icmp_type == ICMP_UNREACH)
		return (VERBOSE_DEST_UNREACH);
	if (icmp_hdr->icmp_type == ICMP_REDIRECT)
		return (VERBOSE_REDIRECT);
	if (icmp_hdr->icmp_type == ICMP_PARAMPROB)
		return (VERBOSE_PARAM_PROB);
	return (NULL);
}

static int	validate_reply(t_ping *ping, struct icmp *icmp_hdr)
{
	if (icmp_hdr->icmp_type != ICMP_ECHOREPLY)
		return (0);
	if (ntohs(icmp_hdr->icmp_id) != (getpid() & 0xffff))
		return (0);
	if (ntohs(icmp_hdr->icmp_seq) != ping->sequence)
		return (0);
	return (1);
}

static struct icmp	*skip_ip_header(unsigned char *buffer, ssize_t len)
{
	struct ip	*ip_hdr;
	int			ip_len;

	if (len < (ssize_t) sizeof(struct ip))
		return (NULL);
	ip_hdr = (struct ip *)buffer;
	ip_len = ip_hdr->ip_hl << 2;
	if (ip_len < (int) sizeof(struct ip))
		return (NULL);
	if (len < ip_len + ICMP_MINLEN)
		return (NULL);
	return ((struct icmp *)(buffer + ip_len));
}

static void	print_verbose_message(size_t bytes, char *src_ip, char *msg)
{
	printf("%zu bytes from %s: %s\n", bytes, src_ip, msg);
}

static int	set_reply_time(t_ping *ping)
{
	if (gettimeofday(&ping->recv_time, NULL) != 0)
		return (-1);
	ping->rtt_ms = (ping->recv_time.tv_sec - ping->send_time.tv_sec) * 1000.0;
	ping->rtt_ms += (ping->recv_time.tv_usec - ping->send_time.tv_usec)
		/ 1000.0;
	return (0);
}

static void	print_ping_reply(size_t bytes, char *src_ip, struct icmp *icmp_hdr,
		t_ping *ping)
{
	printf("%zu bytes from %s: icmp_seq=%u ttl=%d time=%.3f ms\n",
		bytes, src_ip, ntohs(icmp_hdr->icmp_seq), ping->reply_ttl,
		ping->rtt_ms);
}

int	receive_packet(t_ping *ping)
{
	struct sockaddr_in	source_addr;
	struct ip			*ip_hdr;
	struct icmp			*icmp_hdr;
	char				src_ip[INET_ADDRSTRLEN];
	char				*msg;
	size_t				bytes;
	ssize_t				recv_len;

	while (1)
	{
		ping->recv_addr_len = sizeof(source_addr);
		recv_len = recvfrom(ping->sockfd, ping->recv_buffer,
				sizeof(ping->recv_buffer), 0,
				(struct sockaddr *)&source_addr, &ping->recv_addr_len);
		if (recv_len < 0)
		{
			if (errno == EINTR && g_running == 0)
				return (0);
			return (-1);
		}
		ping->recv_len = recv_len;
		ping->recv_addr = source_addr;
		icmp_hdr = skip_ip_header(ping->recv_buffer, recv_len);
		if (icmp_hdr == NULL)
			continue ;
		if (ping->verbose == true)
		{
			msg = (char *)verbose_message(icmp_hdr);
			if (msg != NULL)
			{
				if (inet_ntop(AF_INET, &ping->recv_addr.sin_addr, src_ip,
						sizeof(src_ip)) == NULL)
					return (-1);
				print_verbose_message((size_t)recv_len, src_ip, msg);
				continue ;
			}
		}
		if (validate_reply(ping, icmp_hdr) == 0)
			continue ;
		if (inet_ntop(AF_INET, &ping->recv_addr.sin_addr, src_ip,
				sizeof(src_ip)) == NULL)
			return (-1);
		ip_hdr = (struct ip *)ping->recv_buffer;
		ping->reply_ttl = ip_hdr->ip_ttl;
		bytes = ping->recv_len - (ip_hdr->ip_hl << 2);
		if (set_reply_time(ping) != 0)
			return (-1);
		update_rtt_statistics(ping);
		print_ping_reply(bytes, src_ip, icmp_hdr, ping);
		return (1);
	}
}
