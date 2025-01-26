/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_axis_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:35:04 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 09:12:34 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/game/g_axis.h"
#include "../../includes/game/g_client_script.h"

static void	print_zm_health(t_axis *zm, int yu)
{
	char	*h;
	char	*mh;
	char	*b;
	size_t	len;

	h = xitoa(zm->health);
	if (h)
	{
		mh = xitoa(zm->maxhealth);
		if (mh)
		{
			len = xstrlen(h) + xstrlen(mh) + 4;
			if (xalloc((void **)&b, sizeof(char), len))
			{
				xmemcpy(b, h, xstrlen(h) * sizeof(char));
				xmemcpy(&b[xstrlen(b)], " / ", 3 * sizeof(char));
				xmemcpy(&b[xstrlen(b)], mh, xstrlen(mh) * sizeof(char));
				typewritter("framework", b, (t_vec2){640 - (r_textwidth(b) / 2),
					80 + yu});
				xfree((void **)&b);
			}
			xfree((void **)&mh);
		}
		xfree((void **)&h);
	}
}

void	print_zm(t_player *user, t_axis *zm)
{
	t_shaders	*sh[2];
	t_prim		c;
	double		t;
	int			yu;

	sh[0] = get_img("framework");
	sh[1] = get_anim_img(WORLD_ANIM_ZM, "zombie_000");
	if (user && zm && sh[0] && sh[1])
	{
		if (user->aimbot)
			user->vangle = 0.36f;
		t = linear_scaling(user->vangle, -0.7, 0.7, 1.0);
		yu = (int)((360 * (1 - t) + 450 * t) * user->vangle);
		merge_img(sh[0], sh[1], (t_vec2){502, 104 + yu});
		c = ml_quad((t_vec2){571, 114 + yu}, (t_vec2){150, 10}, 0x030303);
		ml_size(&c, 2);
		ml_savemesh(&c, "framework");
		ml_end(&c);
		c = ml_quad((t_vec2){572, 115 + yu}, (t_vec2){linear_scaling(\
			zm->health, 0, zm->maxhealth, 148), 8}, 0xFF0000);
		ml_savemesh(&c, "framework");
		ml_end(&c);
		print_zm_health(zm, yu);
	}
}

void	zm_death_tracker(t_axis *zm)
{
	if (zm && zm->health <= 0)
	{
		if (zm->is_headshot)
		{
			playsound("zm_headshot", 0, 0, 0);
			add_score(15);
		}
		playsound("zm_die", 0, 0, 0);
		add_score(90);
		zm->alive = 0;
		zm->dmg_color = 0xFF0000;
		--zm->total;
		zm->spawn_time = clock() + 4000000;
	}
}

void	zm_damage_tracker(t_player *user, t_axis *zm)
{
	int	u;

	u = has_perk(PERK_DOUBLETAP) + (user->is_gun_pap * 10);
	if (user && zm && user->weapon)
	{
		if (zm->damage)
			zm->damage = user->weapon->firing;
		if (user->weapon->firing && !zm->damage)
		{
			if (user->vangle > -0.13f && user->vangle <= 0.45f)
			{
				zm->is_headshot = (user->vangle >= 0.34f);
				zm->damage = 1;
				if (zm->is_headshot)
					zm->health -= 20 * (1 + u);
				else
					zm->health -= 10 * (1 + u);
				zm->hitmarker_time = clock() + 1000000;
				zm->dmg_color = 0xFFFFFF;
				add_score(10);
				zm_death_tracker(zm);
			}
		}
	}
}

void	run_zm_logic(void)
{
	t_player	*user;
	t_axis		*zm;
	t_anim		*a;

	zm = get_zm();
	user = get_user();
	a = get_wanim(WORLD_ANIM_ZM);
	if (user && a && zm)
	{
		if (!zm->is_intermission && !zm->alive && clock() >= zm->spawn_time)
			spawn_zm(zm);
		if (user && zm->alive)
		{
			if (clock() >= zm->attack_time && a->loop_anim.x == 9)
			{
				playsound("zm_attack", 0, 0, 0);
				dodamage(user, 0, zm->attack_damage);
				zm->attack_time = clock() + 800000;
			}
			print_zm(user, zm);
			zm_damage_tracker(user, zm);
		}
	}
}
