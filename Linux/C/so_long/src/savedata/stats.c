/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:15:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/20 08:04:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	add_stats(t_core *core, int type)
{
	t_account	*acc;

	acc = get_account(core);
	if (type == g_axis)
	{
		get_game(core)->ents[c_axis]--;
		acc->total_killed++;
		if (acc->total_killed >= 0x7FFFFFFF)
			acc->total_killed = 0x7FFFFFFF;
	}
	else
	{
		get_game(core)->ents[c_collect]--;
		acc->total_collected++;
		if (acc->total_collected >= 0x7FFFFFFF)
			acc->total_collected = 0x7FFFFFFF;
		if (get_game(core)->ents[c_collect] == 0)
			playsound("easter_egg", 0, 0, 1);
	}
}

void	add_steps(t_core *core)
{
	t_account	*acc;

	acc = get_account(core);
	get_client(core)->step++;
	acc->total_step++;
	if (acc->total_step >= 0x7FFFFFFF)
		acc->total_step = 0x7FFFFFFF;
	sl_putnbr(get_client(core)->step);
	print("");
}

void	check_stats(t_core *core)
{
	int			error;
	__uint32_t	max;
	t_account	*acc;

	error = 0;
	max = 0x7FFFFFFF;
	acc = get_account(core);
	if (acc->xp > 0x3B9ACA00 || acc->level > 0xF4240
		|| acc->total_step > max || acc->total_killed > max
		|| acc->total_collected > max)
		error = 1;
	if (acc->xp < 0 || acc->level < 0)
		error = 1;
	if (error)
	{
		print("Something looks weird...");
		print("Save has been reset");
		sl_memset(acc, 0, sizeof(t_account));
	}
}

void	xp_tracker(t_core *core, int type)
{
	int			rem;
	t_account	*acc;

	rem = 0;
	acc = get_account(core);
	if (type == g_axis || type == g_collect)
		add_stats(core, type);
	else
		return ;
	if (acc->level >= 0xF4240)
	{
		acc->level = 0xF4240;
		acc->xp = 0;
		return ;
	}
	acc->xp -= 150 * (1 + flag_status(core, p_x2xp));
	if (acc->xp <= 0)
	{
		playsound("level_up", 0, 0, 1);
		if (acc->xp < 0)
			rem = acc->xp * -1;
		acc->level++;
		acc->xp = (acc->level * 1000) - rem;
	}
}
