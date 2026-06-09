/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:37:22 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:44:09 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	cleanup_ping(t_ping *ping)
{
	if (ping->sockfd >= 0)
		close(ping->sockfd);
	ping->sockfd = -1;
}
