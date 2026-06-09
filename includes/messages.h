/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alifayad <alifayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:48:51 by alifayad          #+#    #+#             */
/*   Updated: 2026/06/08 17:48:56 by alifayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define HELP_MSG \
"Usage\n" \
"  ft_ping [options] <destination>\n" \
"\n" \
"Options:\n" \
"  -v        verbose output\n" \
"  -?        display this help and exit\n"

# define PING_MSG_PREFIX "PING "
# define PING_MSG_OPEN " ("
# define PING_MSG_CLOSE "): "
# define PING_MSG_BYTES " data bytes\n"

# define PING_PAYLOAD_SIZE 56

# define ERR_TOO_MANY_ARGS \
"ft_ping: too many arguments"

# define ERR_MISSING_HOST \
"ft_ping: missing host operand"

# define ERR_INVALID_OPTION \
"ft_ping: invalid option"

# define ERR_RESOLVE_TARGET \
"ft_ping: cannot resolve host"

# define ERR_RAW_SOCKET \
"ft_ping: raw socket error"

# define ERR_RAW_SOCKET_PERM \
"ft_ping: raw socket requires root privileges"

# define ERR_PACKET_BUILD \
"ft_ping: cannot build ICMP packet"

# define ERR_RECEIVE_PACKET \
"ft_ping: cannot receive ICMP packet"

#endif
