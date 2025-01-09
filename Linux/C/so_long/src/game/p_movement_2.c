/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:33:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/18 01:31:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	p_bump_back_x(t_core *core, t_vec3 data)
{
	core->game.client.origin.x = data.x;
	core->game.client.zones.x = data.y;
	core->game.map_rng.x = data.z;
}

static void	p_bump_back_y(t_core *core, t_vec3 data)
{
	core->game.client.origin.y = data.x;
	core->game.client.zones.y = data.y;
	core->game.map_rng.y = data.z;
}

int	p_check_zone(t_core *core, t_vec3 data, int raw)
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
			if (check_player_bump(core, &map[t.y][t.x], t))
			{
				if (!raw)
					return (p_bump_back_x(core, data), 0);
				else
					return (p_bump_back_y(core, data), 0);
			}
			t.x++;
		}
		t.y++;
	}
	return (1);
}
