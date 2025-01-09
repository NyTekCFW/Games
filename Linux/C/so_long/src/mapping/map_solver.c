/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:24:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/21 06:42:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	isinarray(int arr[], int size, int c)
{
	int	i;

	i = 0;
	if (!arr || !*arr || !size)
		return (0);
	while (i < size)
	{
		if (arr[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	is_valid_ent(char c)
{
	int	ent[5];

	sl_memcpy(ent, (int []){g_axis, g_collect, g_exit,
		g_ground, g_player}, sizeof(ent));
	return (isinarray(ent, 5, c));
}

static void	flood_fill(t_core *core, char **map, t_vec2 b, int v)
{
	t_vec2	max;

	max = get_game(core)->map_max;
	map[b.y][b.x] = v + 0x25;
	if (b.y > 0 && is_valid_ent(map[b.y - 1][b.x]))
		flood_fill(core, map, vec2t(b.x, b.y - 1), map[b.y - 1][b.x]);
	if ((b.y < max.y) && is_valid_ent(map[b.y + 1][b.x]))
		flood_fill(core, map, vec2t(b.x, b.y + 1), map[b.y + 1][b.x]);
	if (b.x > 0 && is_valid_ent(map[b.y][b.x - 1]))
		flood_fill(core, map, vec2t(b.x - 1, b.y), map[b.y][b.x - 1]);
	if ((b.x < max.x) && is_valid_ent(map[b.y][b.x + 1]))
		flood_fill(core, map, vec2t(b.x + 1, b.y), map[b.y][b.x + 1]);
}

static void	is_playable(t_core *core, char *ent, t_vec2 ori)
{
	(void)ori;
	if (!is_valid_ent(*ent))
	{
		if (*ent != g_wall && *ent != g_fire)
			*ent -= 0x25;
	}
	else
	{
		if (*ent == g_ground || *ent == g_axis)
			return ;
		print("An entity cannot be reached!");
		win_error(core);
	}
}

void	check_path(t_core *core)
{
	flood_fill(core, get_map(core), get_client(core)->pos, g_player);
	browse_map(core, is_playable);
}
