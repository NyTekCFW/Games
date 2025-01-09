/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:24:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/22 00:00:00 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	is_valid_case(char map)
{
	if (map != g_ground && map != g_collect && map != g_exit)
		return (0);
	return (1);
}

int	check_player_bump(t_core *core, char *map, t_vec2 xy)
{
	t_vec4	mi;

	mi = get_game(core)->map_i;
	if (!is_valid_case(*map))
	{
		if (get_player_presence(core, mi, xy))
		{
			if (clock() >= get_anim(core)->frame[f_sound_effect])
			{
				if (*map == g_wall)
					playsound("wall_bump", 0, 0, 1);
				if (*map == g_fire && !flag_status(core, p_god))
					dodamage(core, 20, g_fire);
				if (*map == g_axis && !flag_status(core, p_god))
					dodamage(core, 30, g_axis);
				get_anim(core)->frame[f_sound_effect] = clock() + 500000;
			}
			get_client(core)->origin = get_client(core)->old_origin;
			return (1);
		}
	}
	return (0);
}

static void	player_case_effect(t_core *core, char *map, t_vec2 xy)
{
	t_vec4	mi;

	mi = get_game(core)->map_i;
	if (is_valid_case(*map))
	{
		if (get_player_presence(core, mi, xy))
		{
			if (*map == g_collect)
			{
				xp_tracker(core, g_collect);
				playsound("rupee", 0, 0, 1);
				*map = g_ground;
			}
			if (*map == g_exit && get_game(core)->ents[c_collect] == 0
				&& get_anim(core)->status[a_exit] == 3)
			{
				get_game(core)->stop_proc = 1;
				set_status(core, status_main);
				playsound("get_master_sword", 1, 1, 0);
				win_exit(core);
			}
			return ;
		}
	}
}

void	p_can_move(t_core *core, char *map, t_vec2 xy)
{
	if (!check_player_bump(core, map, xy))
	{
		player_case_effect(core, map, xy);
	}
}
