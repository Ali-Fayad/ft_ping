/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:36:54 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:44:17 by alifayad         ###   ########.fr       */
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
		exit_with_error(ping, ERR_INVALID_OPTION, EXIT_FAILURE);
}

static void	parse_target(char *arg, t_ping *ping)
{
	if (ping->target != NULL)
	{
		exit_with_error(ping, ERR_TOO_MANY_ARGS, EXIT_FAILURE);
	}
	ping->target = arg;
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
	if (ping->target == NULL && ping->help == false)
	{
		exit_with_error(ping, ERR_MISSING_HOST, EXIT_FAILURE);
	}
}
