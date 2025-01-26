/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_axis_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:16:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 09:18:56 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/game/g_axis.h"
#include "../../includes/game/g_client_script.h"

t_axis	*get_zm(void)
{
	static t_axis	zm = (t_axis){0};

	return (&zm);
}

void	spawn_zm(t_axis *zm)
{
	t_anim		*a;

	a = get_wanim(WORLD_ANIM_ZM);
	if (a)
		a->loop_anim = (t_vec2){0, 0};
	zm->alive = 1;
	zm->damage = 0;
	zm->health = 30 + (int)(zm->round * 10);
	if (zm->health > 1000)
		zm->health = 1000;
	zm->maxhealth = zm->health;
	zm->attack_time = clock() + 500000;
	zm->is_headshot = 0;
	playsound("zm_spawn", 0, 0, 0);
}

void	zm_init(void)
{
	t_axis		*zm;

	zm = get_zm();
	if (zm && !zm->init)
	{
		zm->init = 1;
		zm->round = 1;
		zm->total = (5 + (int)(zm->round * 1.5));
		if (zm->total > 40)
			zm->total = 40;
		zm->attack_damage = (int)fmin(80, 50 * powf(1.1, zm->round - 11));
		if (zm->round < 12)
			zm->attack_damage = 50;
		zm->spawn_time = clock() + 7000000;
	}
}

void	zm_intermission(void)
{
	t_axis		*zm;

	zm = get_zm();
	if (zm)
	{
		if (zm->total <= 0 && !zm->is_intermission)
		{
			playsound("new_round", 0, 0, 0);
			++zm->round;
			zm->total = (5 + (int)(zm->round * 1.5));
			if (zm->total > 40)
				zm->total = 40;
			zm->attack_damage = (int)fmin(80, 50 * powf(1.1, zm->round - 11));
			if (zm->round < 12)
				zm->attack_damage = 50;
			zm->intermission = clock() + 26000000;
			zm->is_intermission = 1;
		}
		else if (zm->is_intermission && clock() >= zm->intermission)
		{
			zm->is_intermission = 0;
			zm->spawn_time = clock() + 4000000;
		}
	}
}

void	run_axis(void)
{
	t_player	*user;

	user = get_user();
	if (user && user->status == USER_ALIVE)
	{
		zm_init();
		zm_intermission();
		run_zm_logic();
	}
}
