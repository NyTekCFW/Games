/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_weapons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:32:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:33:35 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	attribute_data(t_weapon_data *data, char *name, t_vec3 ammo)
{
	data->debugname = fnv1a_hash(name);
	xstrcpy(data->name, name);
	xstrcpy(data->o_name, name);
	data->max_ammo_clip = ammo.x;
	data->max_ammo_stock = ammo.y;
	data->start_ammo_stock = ammo.z;
}

static void	attribute_wpn(t_weapon_data *data, int i)
{
	data[i].id = i;
	xmemset(data[i].name, 0, sizeof(data[i].name));
	xmemset(data[i].o_name, 0, sizeof(data[i].o_name));
	if (i == WPN_NONE)
	{
		attribute_data(&data[i], "None", (t_vec3){0, 0, 0});
		data[i].type = WPN_TYPE_ERROR;
		data[i].fire_mode = WPN_MODE_AUTO;
	}
	else if (i == WPN_M1911)
	{
		attribute_data(&data[i], "M1911", (t_vec3){8, 80, 72});
		data[i].type = WPN_TYPE_PISTOL;
		data[i].fire_mode = WPN_MODE_SINGLE_SHOT;
	}
}

void	bg_register_weapondata(void)
{
	int		i;
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		i = -1;
		while (cub && ++i < WPN_MAX)
			attribute_wpn(cub->weapons, i);
	}
}
