/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+#+#+#+#+   +#+           */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/09 13:10:22 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:10:22 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	print_number(size_t nb)
{
	char	buffer[20];
	int		index;

	index = 0;
	if (nb == 0)
		buffer[index++] = '0';
	while (nb > 0)
	{
		buffer[index++] = (nb % 10) + '0';
		nb /= 10;
	}
	while (index > 0)
	{
		index--;
		write(STDOUT_FILENO, &buffer[index], 1);
	}
}

static void	print_banner(t_ping *ping)
{
	write(STDOUT_FILENO, PING_MSG_PREFIX, sizeof(PING_MSG_PREFIX) - 1);
	write(STDOUT_FILENO, ping->target, str_len(ping->target));
	write(STDOUT_FILENO, PING_MSG_OPEN, sizeof(PING_MSG_OPEN) - 1);
	write(STDOUT_FILENO, ping->resolved_ip, str_len(ping->resolved_ip));
	write(STDOUT_FILENO, PING_MSG_CLOSE, sizeof(PING_MSG_CLOSE) - 1);
	print_number(ping->payload_size);
	write(STDOUT_FILENO, PING_MSG_BYTES, sizeof(PING_MSG_BYTES) - 1);
}

static ssize_t	send_packet(t_ping *ping, char *packet, size_t size)
{
	if (ping->sockfd < 0)
		return (0);
	return (sendto(ping->sockfd, packet, size, 0,
			(struct sockaddr *)&ping->dest_addr, ping->dest_addr_len));
}

int	ft_ping_process(t_ping *ping)
{
	if (ping->help == true)
	{
		print_help();
		return (EXIT_SUCCESS);
	}
	resolve_target(ping);
	print_banner(ping);
	send_packet(ping, NULL, 0);
	return (EXIT_SUCCESS);
}
