/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_register_trigger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:58:29 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:32:47 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/bgame/bg_register_trigger.h"

static size_t	get_trigger_size(void)
{
	size_t	size;
	t_vec2	u;
	t_map	*data;

	data = get_map();
	u = (t_vec2){0, 0};
	size = 0;
	if (data)
	{
		while (u.y < data->height && data->map[u.y])
		{
			u.x = 0;
			while (u.x < data->width && data->map[u.y][u.x])
			{
				if (bg_isinmap(u) && ent_is_trigger(data->map[u.y][u.x]))
					++size;
				++u.x;
			}
			++u.y;
		}
	}
	return (size);
}

static void	fetch_valid_zone(t_ent *ent, char c, t_vec2 u, char **map)
{
	t_vec2	tmp;

	if (ent && map)
	{
		ent->id = c;
		ent->pos = u;
		tmp = (t_vec2){ent->pos.x, ent->pos.y - 1};
		if (bg_isinmap(tmp) && ent_is_ground(map[tmp.y][tmp.x]))
			ent->enabled.x = 1;
		tmp = (t_vec2){ent->pos.x, ent->pos.y + 1};
		if (bg_isinmap(tmp) && ent_is_ground(map[tmp.y][tmp.x]))
			ent->enabled.y = 1;
		tmp = (t_vec2){ent->pos.x - 1, ent->pos.y};
		if (bg_isinmap(tmp) && ent_is_ground(map[tmp.y][tmp.x]))
			ent->enabled.z = 1;
		tmp = (t_vec2){ent->pos.x + 1, ent->pos.y};
		if (bg_isinmap(tmp) && ent_is_ground(map[tmp.y][tmp.x]))
			ent->enabled.w = 1;
	}
}

static void	init_trigger(t_trigger *trig)
{
	size_t	i;
	t_vec2	u;
	t_map	*data;
	char	c;

	data = get_map();
	u = (t_vec2){0, 0};
	i = 0;
	if (data && data->map)
	{
		while (u.y < data->height && data->map[u.y])
		{
			u.x = 0;
			while (u.x < data->width && data->map[u.y][u.x])
			{
				c = data->map[u.y][u.x];
				if (bg_isinmap(u) && ent_is_trigger(c) && i < trig->size)
					fetch_valid_zone(&trig->ents[i++], c, u, data->map);
				++u.x;
			}
			++u.y;
		}
	}
}

int	is_trigger_active(t_player *user, t_ent *ent)
{
	t_vec2	pori;

	pori = (t_vec2){(int)user->origin.x, (int)user->origin.y};
	if (ent->enabled.x && pori.x == ent->pos.x
		&& pori.y == ent->pos.y - 1)
		return (1);
	if (ent->enabled.y && pori.x == ent->pos.x
		&& pori.y == ent->pos.y + 1)
		return (1);
	if (ent->enabled.z && pori.x == ent->pos.x - 1
		&& pori.y == ent->pos.y)
		return (1);
	if (ent->enabled.w && pori.x == ent->pos.x + 1
		&& pori.y == ent->pos.y)
		return (1);
	return (0);
}

t_trigger	*get_trigger(int act)
{
	static t_trigger	*trig = NULL;

	if (act == ACT_INIT && !trig
		&& xalloc((void **)&trig, 1, sizeof(t_trigger)))
	{
		trig->size = get_trigger_size();
		if (xalloc((void **)&trig->ents, trig->size + 1, sizeof(t_ent)))
			init_trigger(trig);
		else
			trig->size = 0;
		return (trig);
	}
	else if (act == ACT_GET && trig)
		return (trig);
	else if (act == ACT_FREE && trig)
	{
		if (trig->ents)
			xfree((void **)&trig->ents);
		xfree((void **)&trig);
	}
	return (NULL);
}
