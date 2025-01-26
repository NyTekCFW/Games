/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_client_script3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:15:14 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:45:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/game/g_axis.h"

void	add_score(__uint32_t add)
{
	t_player	*p;

	p = get_user();
	if (p)
	{
		if ((__uint32_t)p->score + add > 0x7FFFFFFF)
			p->score = 0x7FFFFFFF;
		else
			p->score += add;
	}
}

void	scr_trigger_pap(t_player *user, int *dis)
{
	char			*str;
	t_weapon_data	*d;

	d = get_wpn_data();
	if (d && !user->is_gun_pap)
	{
		*dis = 1;
		str = "Hold [F] for Pack-a-Punch [Cost:$5000]";
		typewritter("framework", str, (t_vec2){315, 650});
		if (scr_purchase(0, NULL, 5000, "pap_sound"))
		{
			user->is_gun_pap = 1;
			take_weapon();
			d[1].debugname = fnv1a_hash("SALLY");
			d[1].max_ammo_clip = 20;
			d[1].max_ammo_stock = 100;
			d[1].fire_mode = WPN_MODE_AUTO;
			xstrcpy(d[1].name, "SALLY");
			give_weapon("SALLY", 0, 0);
			give_max_ammo();
		}
	}
}

void	start_pause(void)
{
	t_axis		*zm;
	t_player	*user;
	__int64_t	time_now;

	time_now = clock();
	zm = get_zm();
	user = get_user();
	if (user && user->status == USER_ALIVE)
	{
		user->status = USER_PAUSED;
		user->regentime -= time_now;
		user->immunity -= time_now;
		if (zm)
		{
			zm->attack_time -= time_now;
			zm->intermission -= time_now;
			zm->spawn_time -= time_now;
			zm->hitmarker_time -= time_now;
		}
	}
}

void	stop_pause(void)
{
	t_axis		*zm;
	t_player	*user;
	__int64_t	time_now;

	time_now = clock();
	zm = get_zm();
	user = get_user();
	if (user && user->status == USER_PAUSED)
	{
		user->status = USER_ALIVE;
		user->regentime += time_now;
		user->immunity += time_now;
		if (zm)
		{
			zm->attack_time += time_now;
			zm->intermission += time_now;
			zm->spawn_time += time_now;
			zm->hitmarker_time += time_now;
		}
	}
}
