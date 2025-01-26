/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:26:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 09:11:37 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/core/parsing.h"
#include "../../includes/bgame/bg_register_trigger.h"

static void	bg_copy_map(t_map *g, t_file *f)
{
	int		i;
	size_t	len;

	i = 0;
	if (xalloc((void **)&g->map, sizeof(char *), f->height + 1))
	{
		while (i < f->height)
		{
			if (xalloc((void **)&g->map[i], sizeof(char), f->width + 1))
			{
				len = xstrlen(f->map[f->begin + i]);
				xmemcpy(g->map[i], f->map[f->begin + i], sizeof(char) * len);
				++i;
			}
		}
	}
}

void	bg_map_register(void)
{
	t_map	*_map;
	t_file	*file;

	_map = get_map();
	file = get_parsing_file(ACT_GET);
	_map->dimension = 64;
	_map->height = file->height;
	_map->width = file->width;
	_map->color_ceil = file->color[1];
	_map->color_floor = file->color[0];
	_map->color_rgb = 0xFFFFFF;
	if (_map && file && file->map)
	{
		bg_copy_map(_map, file);
		get_trigger(ACT_INIT);
	}
}

int	bg_isinmap(t_vec2 v)
{
	t_map	*_map;

	_map = get_map();
	if (_map)
	{
		if (v.x >= 0 && v.x < _map->width)
			if (v.y >= 0 && v.y < _map->height)
				return (1);
	}
	return (0);
}

int	bg_can_walk(t_vec2 v)
{
	t_map		*_map;
	t_player	*user;
	char		c;

	user = get_user();
	_map = get_map();
	if (user && _map && bg_isinmap(v))
	{
		c = _map->map[v.y][v.x];
		if (ent_is_ground(c))
		{
			user->velocity += 0.2;
			if (user->velocity > 1.6f)
				user->velocity = 1.6f;
			return (1);
		}
		if (ent_is_trap(c))
			dodamage(user, c, 35);
	}
	return (0);
}
