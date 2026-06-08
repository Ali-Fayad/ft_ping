/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:35:27 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:35:32 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ping
{
	char	*hostname;
	bool	verbose;
	bool	help;
}	t_ping;

void	init_ping(t_ping *ping);

void	parse_args(int argc, char **argv, t_ping *ping);

void	cleanup_ping(t_ping *ping);

void	exit_with_error(
			t_ping *ping,
			char *msg,
			int code);

#endif