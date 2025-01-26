/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:25:14 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:25:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_client_move.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/core/parsing.h"
#include "../../includes/bgame/bg_register_trigger.h"
#include "../../includes/game/g_axis.h"

t_vec2	get_anim_hand_pos(t_player *user)
{
	static int	rel = 0;
	float		x;
	double		g;
	t_vec2		p;
	t_vec2		*r;

	if (user->weapon && user->weapon->reloading)
		return (rel = 1, (t_vec2){395, 130});
	if (rel)
		return (rel = 0, (t_vec2){395, 130});
	r = get_move_render();
	p = (t_vec2){620, 135};
	g = scr_get_movespeed();
	x = 1.0;
	if (g >= 0.15)
		x = 1.5;
	p.x += ((r->x * x) * user->velocity) * *(double *)getvar("cg_gun_x");
	p.y += ((r->y * x) * user->velocity) * *(double *)getvar("cg_gun_y");
	return (p);
}

void	health_regen(t_player *user)
{
	int	has_quickregen;
	int	has_juggernog;
	int	diff;

	has_quickregen = has_perk(PERK_QUICKREGEN);
	has_juggernog = has_perk(PERK_JUGGERNOG);
	diff = (150 * (1 + has_juggernog)) - user->health;
	if (clock() > user->regentime && diff > 0)
	{
		user->health += 3 * (1 + has_quickregen);
		if (user->health > 150 * (1 + has_juggernog))
			user->health = 150 * (1 + has_juggernog);
	}
}

void	velocity_tracker(void)
{
	t_key		*key[4];
	t_player	*user;

	key[0] = get_key(BUTTON_MOVE_FORWARD);
	key[1] = get_key(BUTTON_MOVE_BACKWARD);
	key[2] = get_key(BUTTON_MOVE_LEFT);
	key[3] = get_key(BUTTON_MOVE_RIGHT);
	user = get_user();
	if (user && key[0] && key[1] && key[2] && key[3])
	{
		if (!key_pressed(key[0]->id) && !key_pressed(key[1]->id)
			&& !key_pressed(key[2]->id && !key_pressed(key[3]->id)))
		{
			user->velocity -= 0.2;
			if (user->velocity < 0)
				user->velocity = 0;
		}
	}
}

void	run_user(void)
{
	t_shaders	*sh[2];
	t_player	*user;

	user = get_user();
	if (user && user->status == USER_ALIVE)
	{
		if (user->weapon)
		{
			if (user->weapon->firing)
				run_weapon_anim("_fire_000", WPN_FRAME_FIRE);
			else if (user->weapon->reloading)
				run_weapon_anim("_reload_000", WPN_FRAME_RELOAD);
			else
				run_weapon_anim("_walk_000", WPN_FRAME_WALK);
			sh[0] = get_img("framework");
			sh[1] = get_img(user->weapon->anim_buffer);
			merge_img(sh[0], sh[1], get_anim_hand_pos(user));
		}
		health_regen(user);
		draw_minimap();
		hud_render();
		scr_find_trigger_active();
		scr_ammo_tracker();
		velocity_tracker();
	}
}
