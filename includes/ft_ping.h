/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:35:27 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:29:15 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdbool.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <string.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
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
	bool				verbose;
	bool				help;
}	t_ping;

void	init_ping(t_ping *ping);

void	parse_args(int argc, char **argv, t_ping *ping);

void	cleanup_ping(t_ping *ping);

void	print_help(void);

void	exit_with_error(t_ping *ping, char *msg, int code);

int		resolve_target(t_ping *ping);

int		ft_ping_process(t_ping *ping);

#endif
