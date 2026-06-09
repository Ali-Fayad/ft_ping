/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:35:27 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 16:45:15 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdbool.h>
# include <arpa/inet.h>
# include <errno.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>
# include <stdint.h>
# include <netinet/ip.h>
# include <sys/time.h>
# include <string.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <signal.h>
# include "messages.h"

typedef struct s_ping
{
	char				*target;
	char				resolved_ip[INET_ADDRSTRLEN];
	struct sockaddr_in	dest_addr;
	socklen_t			dest_addr_len;
	int					sockfd;
	size_t				payload_size;
	size_t				packet_size;
	unsigned char		packet[ICMP_MINLEN + PING_PAYLOAD_SIZE];
	unsigned char		recv_buffer[1500];
	ssize_t				recv_len;
	struct sockaddr_in	recv_addr;
	socklen_t			recv_addr_len;
	uint16_t			sequence;
	struct timeval		send_time;
	struct timeval		recv_time;
	double				rtt_ms;
	double				rtt_min;
	double				rtt_max;
	double				rtt_sum;
	size_t				packets_transmitted;
	size_t				packets_received;
	int					reply_ttl;
	bool				verbose;
	bool				help;
	bool				running;
}	t_ping;

extern volatile sig_atomic_t	g_running;

void		init_ping(t_ping *ping);

void		parse_args(int argc, char **argv, t_ping *ping);

void		cleanup_ping(t_ping *ping);

void		print_help(void);

void		exit_with_error(t_ping *ping, char *msg, int code);

int			resolve_target(t_ping *ping);

int			open_icmp_socket(t_ping *ping);

void		close_icmp_socket(t_ping *ping);

int			build_echo_request(t_ping *ping, uint16_t sequence);

uint16_t	icmp_checksum(void *data, size_t len);

int			receive_packet(t_ping *ping);

int			ft_ping_process(t_ping *ping);

void		handle_socket_error(t_ping *ping);

void		setup_signal_handler(void);
void		handle_sigint(int sig);

void		print_statistics(t_ping *ping);

void		update_rtt_statistics(t_ping *ping);

#endif
