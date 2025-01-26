/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:45:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:38:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	asset_data_stock(t_vec2 u, t_weapon *cur, t_weapon_data *data)
{
	xstrcpy(cur->info_buffer + xstrlen(cur->info_buffer), " / ");
	u.x = (data->max_ammo_stock < 100) + (data->max_ammo_stock < 10);
	u.y = xstrlen(cur->info_buffer);
	while (u.x < 3)
	{
		if (data->max_ammo_stock >= 100 && u.x == 0)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_stock / 100);
		else if (data->max_ammo_stock >= 10 && u.x == 1)
			cur->info_buffer[u.y] = 0x30 + ((cur->ammo_stock / 10) % 10);
		else if (u.x == 2)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_stock % 10);
		u.x++;
		u.y++;
	}
}

static void	asset_data_clip(t_weapon *cur, t_weapon_data *data)
{
	t_vec2	u;

	xstrcpy(cur->info_buffer, data->name);
	cur->info_buffer[xstrlen(cur->info_buffer)] = '\n';
	u.x = (data->max_ammo_clip < 100) + (data->max_ammo_clip < 10);
	u.y = xstrlen(cur->info_buffer);
	while (u.x < 3)
	{
		if (data->max_ammo_clip >= 100 && u.x == 0)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_clip / 100);
		else if (data->max_ammo_clip >= 10 && u.x == 1)
			cur->info_buffer[u.y] = 0x30 + ((cur->ammo_clip / 10) % 10);
		else if (u.x == 2)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_clip % 10);
		u.x++;
		u.y++;
	}
	asset_data_stock(u, cur, data);
}

void	get_weapon_info(void)
{
	t_weapon		*cur;
	t_weapon_data	*data;
	t_player		*user;

	user = get_user();
	data = get_wpn_data();
	if (user && user->weapon && data)
	{
		cur = user->weapon;
		xmemset(cur->info_buffer, 0, 64);
		asset_data_clip(cur, &data[cur->id]);
	}
}
