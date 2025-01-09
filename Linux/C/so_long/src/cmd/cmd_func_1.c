/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_func_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:48:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/07 05:39:34 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	cmd_speed_f(t_core *core)
{
	if (get_client(core)->flags & p_speed)
		flag_clear(core, p_speed);
	else
		flag_set(core, p_speed);
	flag_print("Speed x2: ", (get_client(core)->flags & p_speed));
}

void	cmd_quit_f(t_core *core)
{
	win_exit(core);
}
