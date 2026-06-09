/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:35:20 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 14:58:53 by alifayad         ###   ########.fr       */
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

static ssize_t	send_packet(t_ping *ping)
{
	if (gettimeofday(&ping->send_time, NULL) != 0)
		return (-1);
	return (sendto(ping->sockfd, ping->packet, ping->packet_size, 0,
			(struct sockaddr *)&ping->dest_addr, ping->dest_addr_len));
}

static void	setup_sigint_handler(t_ping *ping)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_with_error(ping, ERR_SIGINT_HANDLER, EXIT_FAILURE);
}

int	ft_ping_process(t_ping *ping)
{
	if (ping->help == true)
	{
		print_help();
		return (EXIT_SUCCESS);
	}
	resolve_target(ping);
	if (open_icmp_socket(ping) != 0)
		handle_socket_error(ping);
	print_banner(ping);
	setup_sigint_handler(ping);
	while (g_running == 1)
	{
		if (build_echo_request(ping, ping->sequence) != 0)
			exit_with_error(ping, ERR_PACKET_BUILD, EXIT_FAILURE);
		if (send_packet(ping) < 0)
		{
			if (errno == EINTR && g_running == 0)
				break ;
			exit_with_error(ping, ERR_RAW_SOCKET, EXIT_FAILURE);
		}
		ping->packets_transmitted++;
		if (receive_packet(ping) != 1)
		{
			if (g_running == 0)
				break ;
			exit_with_error(ping, ERR_RECEIVE_PACKET, EXIT_FAILURE);
		}
		ping->sequence++;
		sleep(1);
	}
	print_statistics(ping);
	return (EXIT_SUCCESS);
}
