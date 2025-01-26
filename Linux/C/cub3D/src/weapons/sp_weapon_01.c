/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:54:08 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:38:38 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static int	get_weapon_by_name(char *name)
{
	t_weapon_data	*weapons;
	int				i;

	weapons = get_wpn_data();
	i = 0;
	if (weapons)
	{
		while (i < WPN_MAX)
		{
			if (weapons[i].debugname == fnv1a_hash(name))
				return (weapons[i].id);
			i++;
		}
	}
	return (0);
}

void	give_weapon(char *name, __uint32_t clip, __uint32_t stock)
{
	t_weapon		*weap;
	t_weapon_data	*weapons;
	t_player		*user;
	int				id;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons)
	{
		weap = user->weapon;
		id = get_weapon_by_name(name);
		weap->id = id;
		weap->ammo_clip = weapons[id].max_ammo_clip;
		weap->ammo_stock = weapons[id].start_ammo_stock;
		if (clip != 0xFFFF)
			weap->ammo_clip = clip;
		if (stock != 0xFFFF)
			weap->ammo_stock = stock;
		weap->reloading = 0;
		weap->no_ammo = (!clip && !stock);
	}
}

int	can_get_ammo(void)
{
	t_weapon		*weap;
	t_weapon_data	*weapons;
	t_player		*user;
	__uint32_t		total;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons)
	{
		weap = user->weapon;
		total = (weapons[weap->id].max_ammo_clip
				+ weapons[weap->id].max_ammo_stock);
		total -= (weap->ammo_clip + weap->ammo_stock);
		return (total > 0);
	}
	return (0);
}

void	give_max_ammo(void)
{
	t_weapon		*weap;
	t_weapon_data	*weapons;
	t_player		*user;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons)
	{
		weap = user->weapon;
		weap->ammo_clip = weapons[weap->id].max_ammo_clip;
		weap->ammo_stock = weapons[weap->id].max_ammo_stock;
		weap->reloading = 0;
		weap->no_ammo = 0;
	}
}

void	take_weapon(void)
{
	t_weapon		*weap;
	t_weapon_data	*weapons;
	t_player		*user;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons)
	{
		weap = user->weapon;
		weap->ammo_clip = weapons[WPN_NONE].max_ammo_clip;
		weap->ammo_stock = weapons[WPN_NONE].max_ammo_stock;
		weap->id = WPN_NONE;
		weap->reloading = 0;
		weap->no_ammo = 0;
	}
}
