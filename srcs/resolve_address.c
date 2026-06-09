/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:28:54 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:29:08 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	copy_resolved_addr(t_ping *ping, struct addrinfo *res)
{
	struct sockaddr_in	*addr;

	addr = (struct sockaddr_in *)res->ai_addr;
	ping->dest_addr = *addr;
	ping->dest_addr_len = sizeof(ping->dest_addr);
}

static void	fill_resolved_ip(t_ping *ping)
{
	if (inet_ntop(AF_INET, &ping->dest_addr.sin_addr,
			ping->resolved_ip, sizeof(ping->resolved_ip)) == NULL)
		exit_with_error(ping, ERR_RESOLVE_TARGET, EXIT_FAILURE);
}

int	resolve_target(t_ping *ping)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				status;

	res = NULL;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	status = getaddrinfo(ping->target, NULL, &hints, &res);
	if (status != 0)
		exit_with_error(ping, ERR_RESOLVE_TARGET, EXIT_FAILURE);
	copy_resolved_addr(ping, res);
	freeaddrinfo(res);
	fill_resolved_ip(ping);
	return (EXIT_SUCCESS);
}
