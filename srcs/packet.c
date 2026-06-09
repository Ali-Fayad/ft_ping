/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+#+#+#+#+   +#+           */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/09 13:10:22 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:10:22 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	build_echo_request(t_ping *ping, uint16_t sequence)
{
	struct icmp	*icmp;

	if (ping->payload_size > PING_PAYLOAD_SIZE)
		return (-1);
	ping->packet_size = ICMP_MINLEN + ping->payload_size;
	memset(ping->packet, 0, sizeof(ping->packet));
	icmp = (struct icmp *)ping->packet;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = htons((uint16_t)getpid() & 0xffff);
	icmp->icmp_seq = htons(sequence);
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = icmp_checksum(ping->packet, ping->packet_size);
	return (0);
}
