/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:36:54 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:36:58 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	is_option(char *arg)
{
	return (arg[0] == '-');
}

static void	parse_option(char *arg, t_ping *ping)
{
	if (arg[1] == 'v' && arg[2] == '\0')
		ping->verbose = true;
	else if (arg[1] == '?' && arg[2] == '\0')
		ping->help = true;
	else
		exit_with_error(
			ping,
			"ft_ping: invalid option",
			EXIT_FAILURE);
}

static void	parse_target(char *arg, t_ping *ping)
{
	if (ping->hostname != NULL)
	{
		exit_with_error(
			ping,
			"ft_ping: too many arguments",
			EXIT_FAILURE);
	}
	ping->hostname = arg;
}

void	parse_args(int argc, char **argv, t_ping *ping)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_option(argv[i]))
			parse_option(argv[i], ping);
		else
			parse_target(argv[i], ping);
		i++;
	}
	if (ping->hostname == NULL && ping->help == false)
	{
		exit_with_error(
			ping,
			"ft_ping: missing host operand",
			EXIT_FAILURE);
	}
}