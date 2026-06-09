/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:36:11 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 14:16:26 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_ping(t_ping *ping)
{
	ping->target = NULL;
	ping->resolved_ip[0] = '\0';
	ping->dest_addr_len = 0;
	ping->sockfd = -1;
	ping->payload_size = PING_PAYLOAD_SIZE;
	ping->packet_size = ICMP_MINLEN + PING_PAYLOAD_SIZE;
	ping->recv_len = 0;
	ping->recv_addr_len = 0;
	ping->sequence = 1;
	ping->rtt_ms = 0.0;
	ping->rtt_min = 0.0;
	ping->rtt_max = 0.0;
	ping->rtt_sum = 0.0;
	ping->packets_transmitted = 0;
	ping->packets_received = 0;
	ping->reply_ttl = 0;
	ping->verbose = false;
	ping->help = false;
}
