/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:35:56 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:36:30 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(int argc, char **argv)
{
	t_ping	ping;

	init_ping(&ping);
	parse_args(argc, argv, &ping);
	cleanup_ping(&ping);
	return (EXIT_SUCCESS);
}
