/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_attack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:20:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/18 05:25:19 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	detect_kill(t_core *core, t_vec2 lkat, t_vec2 t)
{
	char	**map;
	t_vec4	mi;

	mi = get_game(core)->map_i;
	map = get_map(core);
	if (get_player_presence(core, mi, t))
	{
		if (map[t.y + lkat.y][t.x + lkat.x] == g_axis
			|| map[t.y + lkat.y][t.x + lkat.x] == 'T')
		{
			map[t.y + lkat.y][t.x + lkat.x] = g_ground;
			playsound("monster_killed", 0, 0, 1);
			xp_tracker(core, g_axis);
			get_game(core)->ents[c_axis]--;
		}
	}
}

static void	find_axis(t_core *core, t_vec2 lkat)
{
	char	**map;
	t_vec2	t;

	map = get_map(core);
	t = vec2t(0, 0);
	while (t.y < core->game.map_max.y && map[t.y])
	{
		t.x = 0;
		while (t.x < core->game.map_max.x && map[t.y][t.x])
		{
			detect_kill(core, lkat, t);
			t.x++;
		}
		t.y++;
	}
}

void	try_attack(t_core *core)
{
	t_client	*cl;
	t_vec2		lkat;

	cl = get_client(core);
	lkat = vec2t(0, 0);
	if (cl->dir == kb_up)
		lkat.y = -1;
	else if (cl->dir == kb_down)
		lkat.y = 1;
	else if (cl->dir == kb_left)
		lkat.x = -1;
	else if (cl->dir == kb_right)
		lkat.x = 1;
	find_axis(core, lkat);
}
