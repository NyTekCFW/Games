/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:15:20 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:51:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_sound.h"

static void	wloopf(int id, t_weapon *wpn, t_weapon_data *data, t_vec2 *v)
{
	if (id == WPN_FRAME_RELOAD && has_perk(PERK_SPEEDCOLA))
		++v->x;
	if (id == WPN_FRAME_FIRE && has_perk(PERK_DOUBLETAP))
		v->x += 1 + !wpn->firing;
	if (v->x >= data->frame[id])
	{
		v->y = 1;
		if (id == WPN_FRAME_FIRE)
		{
			wpn->firing = 0;
			v->y = 0;
			v->x = 0;
		}
		else if (id == WPN_FRAME_RELOAD)
		{
			wpn->reloading = 0;
			v->y = 0;
			v->x = 0;
		}
	}
}

static void	walk_loop_anim(t_weapon *wpn, t_vec2 *v, size_t len, int id)
{
	t_weapon_data	*data;

	data = get_wpn_data();
	if (data)
	{
		data = &data[wpn->id];
		if (v->y == 0 && v->x < data->frame[id])
		{
			++v->x;
			wloopf(id, wpn, data, v);
		}
		else if (v->y == 1 && v->x >= 0)
		{
			v->x -= 1;
			if (v->x < 0)
			{
				v->y = 0;
				v->x = 0;
				wpn->anim_buffer[len - 1] = '0';
			}
		}
	}
}

static void	runw(int id, t_weapon *wpn, t_vec2 *v)
{
	if (wpn->last_id != id)
	{
		wpn->last_id = id;
		*v = (t_vec2){0, 0};
	}
	if (id == WPN_FRAME_RELOAD)
	{
		if (v->x == 1 + has_perk(PERK_SPEEDCOLA))
			playsound("out_clip", 0, 0, 1);
		else if (v->x == 21 + has_perk(PERK_SPEEDCOLA))
			playsound("in_clip", 0, 0, 1);
		else if (v->x == 30)
			playsound("bullet_load", 0, 0, 1);
	}
}

void	run_weapon_anim(const char *anim, int id)
{
	static t_vec2	v = {0, 0};
	size_t			len;
	t_weapon		*wpn;
	t_weapon_data	*weapons;
	t_player		*user;

	user = get_user();
	weapons = get_wpn_data();
	if (user && user->weapon && weapons)
	{
		wpn = user->weapon;
		runw(id, wpn, &v);
		xstrcpy(wpn->anim_buffer, weapons[wpn->id].o_name);
		len = xstrlen(wpn->anim_buffer);
		xstrcpy(wpn->anim_buffer + len, anim);
		len = xstrlen(wpn->anim_buffer);
		wpn->anim_buffer[len - 3] = 0x30 + (v.x / 100);
		wpn->anim_buffer[len - 2] = 0x30 + ((v.x / 10) % 10);
		wpn->anim_buffer[len - 1] = 0x30 + (v.x % 10);
		walk_loop_anim(wpn, &v, len, id);
	}
}
