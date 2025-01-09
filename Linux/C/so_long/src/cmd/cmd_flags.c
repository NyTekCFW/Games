/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:48:26 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/21 03:28:31 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	flag_set(t_core *core, __uint32_t flag)
{
	get_client(core)->flags |= flag;
}

void	flag_clear(t_core *core, __uint32_t flag)
{
	get_client(core)->flags &= ~flag;
}

int	flag_status(t_core *core, __uint32_t flag)
{
	if (get_client(core)->flags & flag)
		return (1);
	return (0);
}

void	flag_print(char	*str, __uint32_t status)
{
	write(1, "\033[1m", 4);
	write(1, str, sl_strlen(str));
	if (status)
		write(1, "\033[32mON", 7);
	else
		write(1, "\033[31mOFF", 8);
	write(1, "\033[0m\n", 5);
}
