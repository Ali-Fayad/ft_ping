/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:36:11 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:36:21 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_ping(t_ping *ping)
{
	ping->hostname = NULL;
	ping->verbose = false;
	ping->help = false;
}
