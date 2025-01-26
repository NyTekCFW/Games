/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:25:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:30:26 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/clientscript/player_command.h"

int	has_perk(int perk)
{
	t_player	*user;

	user = get_user();
	if (user && user->perks & perk)
		return (1);
	return (0);
}

static void	set_initial_angle(t_player *user, char c)
{
	t_vec2f	dir;
	t_vec2f	plane;

	if (c == 'W')
	{
		dir = (t_vec2f){-1.f, 0};
		plane = (t_vec2f){0, 0.66f};
	}
	else if (c == 'E')
	{
		dir = (t_vec2f){1.f, 0};
		plane = (t_vec2f){0, -0.66f};
	}
	else if (c == 'N')
	{
		dir = (t_vec2f){0, -1.f};
		plane = (t_vec2f){-0.66f, 0};
	}
	else if (c == 'S')
	{
		dir = (t_vec2f){0, 1.f};
		plane = (t_vec2f){0.66f, 0};
	}
	user->dir = dir;
	user->plane = plane;
}

static t_vec2f	get_initial_origin(t_player *user)
{
	t_map	*_map;
	t_vec2	u;
	char	c;

	_map = get_map();
	u = (t_vec2){-1, -1};
	if (user && _map && _map->map)
	{
		while (++u.y < _map->height && _map->map[u.y])
		{
			u.x = -1;
			while (++u.x < _map->width && _map->map[u.y][u.x])
			{
				c = _map->map[u.y][u.x];
				if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
				{
					set_initial_angle(user, c);
					_map->map[u.y][u.x] = '0';
					return ((t_vec2f){(double)u.x, (double)u.y});
				}
			}
		}
	}
	return ((t_vec2f){1, 1});
}

void	bg_registerclient(void)
{
	t_player	*client;
	t_dvars		*dvar;

	client = get_user();
	dvar = dvar_findvar("g_speed");
	if (client)
	{
		client->status = USER_ALIVE;
		client->origin = get_initial_origin(client);
		client->vangle = 0;
		client->health = 150;
		client->score = 500;
		client->regentime = clock();
		client->immunity = clock();
		if (dvar)
			client->speed = dvar->dvalue;
		p_reg_commands();
		if (xalloc((void **)&client->weapon, sizeof(t_weapon), 1))
			give_weapon("M1911", 0xFFFF, 0xFFFF);
	}
}
