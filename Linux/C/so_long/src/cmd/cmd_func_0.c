/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_func_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:48:35 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/26 10:53:24 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	send_command(t_core *core)
{
	if (get_status(core) == status_pause && !get_cmd(core)->is_open)
	{
		sl_memset(get_cmd(core)->buffer, 0, 32);
		get_cmd(core)->cursor = 0;
		get_cmd(core)->is_open = 1;
		set_status(core, status_cmd);
	}
}

void	cmd_god_f(t_core *core)
{
	if (get_client(core)->flags & p_god)
		flag_clear(core, p_god);
	else
		flag_set(core, p_god);
	flag_print("Invulnerability: ", (get_client(core)->flags & p_god));
}

void	cmd_info_f(t_core *core)
{
	if (get_client(core)->flags & p_info)
		flag_clear(core, p_info);
	else
		flag_set(core, p_info);
	flag_print("Show Info: ", (get_client(core)->flags & p_info));
}

void	cmd_x2xp_f(t_core *core)
{
	if (get_client(core)->flags & p_x2xp)
		flag_clear(core, p_x2xp);
	else
		flag_set(core, p_x2xp);
	flag_print("Double XP: ", (get_client(core)->flags & p_x2xp));
}
