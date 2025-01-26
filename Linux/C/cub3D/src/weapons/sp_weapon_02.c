/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:16:42 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:57:58 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_sound.h"

static int	get_ammo_count(t_weapon *weap, t_weapon_data *data)
{
	int	p;

	p = weap->ammo_stock - (data->max_ammo_clip - weap->ammo_clip);
	if (p <= 0)
		return (weap->ammo_stock);
	return (weap->ammo_stock - p);
}

static void	wfired(t_player *user, t_weapon *weap, clock_t *cd)
{
	char	*str;

	if (weap->ammo_clip > 0 && clock() >= *cd && !weap->firing)
	{
		*cd = clock() + 333953;
		*cd -= 55659 * has_perk(PERK_DOUBLETAP);
		*cd -= 8294 * user->is_gun_pap;
		weap->ammo_clip -= 1;
		user->velocity = 1.6f;
		weap->firing = 1;
		str = "m1911_fire";
		if (user->is_gun_pap)
			str = "m1911_pap_fire";
		playsound(str, 0, 0, 1);
		user->vangle += 0.005;
		if (user->vangle >= 0.7)
			user->vangle = 0.7;
		if (weap->ammo_stock == 0 && weap->ammo_clip == 0)
			weap->no_ammo = 1;
	}
}

void	weapon_fired(void)
{
	static clock_t	cd = 0;
	t_weapon		*weap;
	t_weapon_data	*weapons;
	t_player		*user;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons
		&& user->status == USER_ALIVE)
	{
		weap = user->weapon;
		if (weap->id != WPN_NONE)
		{
			if (!weap->no_ammo && !weap->reloading)
				wfired(user, weap, &cd);
			if (weap->ammo_clip == 0)
				playsound("out_of_ammo", 0, 0, 1);
		}
	}
}

void	weapon_reload(void)
{
	t_weapon		*weap;
	t_weapon_data	*weapons;
	t_player		*user;
	int				p;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons
		&& user->status == USER_ALIVE)
	{
		weap = user->weapon;
		if (weap->id != WPN_NONE && !weap->no_ammo && !weap->reloading
			&& !weap->firing)
		{
			if (weap->ammo_clip < weapons[weap->id].max_ammo_clip
				&& weap->ammo_stock > 0)
			{
				weap->reloading = 1;
				p = get_ammo_count(weap, &weapons[weap->id]);
				weap->ammo_clip += p;
				weap->ammo_stock -= p;
			}
		}
	}
}
