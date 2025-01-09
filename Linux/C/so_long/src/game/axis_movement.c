/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:43:45 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/16 21:30:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	a_inc2(t_core *core, char *ent, t_vec2 ori, t_vec2 move)
{
	t_vec2	max;
	char	**map;
	t_vec4	mi;

	mi = get_game(core)->map_i;
	max = get_game(core)->map_max;
	map = get_map(core);
	if (move.y && ori.y + move.y >= 1 && ori.y + move.y < max.y
		&& map[ori.y + move.y][ori.x] == g_ground)
	{
		if (get_player_presence(core, mi, vec2t(ori.x, ori.y + move.y))
			&& !flag_status(core, p_god))
			dodamage(core, 15, g_axis);
		else if (!get_player_presence(core, mi, vec2t(ori.x, ori.y + move.y)))
		{
			map[ori.y + move.y][ori.x] = 'T';
			*ent = g_ground;
		}
	}
}

static int	a_inc(t_core *core, char *ent, t_vec2 ori, t_vec2 move)
{
	t_vec2	max;
	char	**map;
	t_vec4	mi;

	mi = get_game(core)->map_i;
	max = get_game(core)->map_max;
	map = get_map(core);
	if (move.x && ori.x + move.x >= 1 && ori.x + move.x < max.x
		&& map[ori.y][ori.x + move.x] == g_ground)
	{
		if (get_player_presence(core, mi, vec2t(ori.x + move.x, ori.y))
			&& !flag_status(core, p_god))
			dodamage(core, 15, g_axis);
		else if (!get_player_presence(core, mi, vec2t(ori.x + move.x, ori.y)))
		{
			map[ori.y][ori.x + move.x] = 'T';
			*ent = g_ground;
			return (1);
		}
	}
	return (0);
}

void	a_print(t_core *core, char *ent, t_vec2 ori)
{
	(void)core;
	(void)ori;
	if (*ent != 'T')
		return ;
	*ent = g_axis;
}

void	a_move(t_core *core, char *ent, t_vec2 ori)
{
	int		res;
	t_vec2	move;

	if (*ent != g_axis || *ent == 'T')
		return ;
	*ent = 'T';
	res = randintrange(0, 100);
	if (res <= 25)
		move = vec2t(1, 0);
	else if (res <= 50)
		move = vec2t(-1, 0);
	else if (res <= 75)
		move = vec2t(0, 1);
	else if (res <= 100)
		move = vec2t(0, -1);
	if (!a_inc(core, ent, ori, move))
		a_inc2(core, ent, ori, move);
}
