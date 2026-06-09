/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+#+#+#+#+   +#+           */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/09 13:10:22 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:10:22 by alifayad         +#+#+#+#+#+   +#+           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_ping.h"

void	update_rtt_statistics(t_ping *ping)
{
	ping->packets_received++;
	ping->rtt_sum += ping->rtt_ms;
	if (ping->packets_received == 1)
	{
		ping->rtt_min = ping->rtt_ms;
		ping->rtt_max = ping->rtt_ms;
	}
	else
	{
		if (ping->rtt_ms < ping->rtt_min)
			ping->rtt_min = ping->rtt_ms;
		if (ping->rtt_ms > ping->rtt_max)
			ping->rtt_max = ping->rtt_ms;
	}
}

void	print_statistics(t_ping *ping)
{
	double	loss;
	double	avg;

	printf("\n--- %s ping statistics ---\n", ping->target);
	if (ping->packets_transmitted == 0)
		loss = 0.0;
	else
		loss = ((double)(ping->packets_transmitted - ping->packets_received)
				* 100.0) / (double)ping->packets_transmitted;
	printf("%zu packets transmitted, %zu received, %.0f%% packet loss\n",
		ping->packets_transmitted, ping->packets_received, loss);
	if (ping->packets_received == 0)
		return ;
	avg = ping->rtt_sum / (double)ping->packets_received;
	printf("round-trip min/avg/max = %.3f/%.3f/%.3f ms\n",
		ping->rtt_min, avg, ping->rtt_max);
}
