/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:42:02 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:42:04 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	open_icmp_socket(t_ping *ping)
{
	ping->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping->sockfd < 0)
		return (-1);
	return (0);
}

void	close_icmp_socket(t_ping *ping)
{
	if (ping->sockfd >= 0)
		close(ping->sockfd);
	ping->sockfd = -1;
}
