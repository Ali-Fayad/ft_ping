/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:35:56 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/09 13:12:49 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(int argc, char **argv)
{
	t_ping	ping;
	int		status;

	init_ping(&ping);
	parse_args(argc, argv, &ping);
	status = ft_ping_process(&ping);
	cleanup_ping(&ping);
	return (status);
}
