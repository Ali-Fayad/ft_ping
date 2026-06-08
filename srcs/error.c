/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:37:07 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:37:09 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(STDERR_FILENO, &msg[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
}

void	exit_with_error(t_ping *ping, char *msg, int code)
{
	cleanup_ping(ping);
	print_error(msg);
	exit(code);
}