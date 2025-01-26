/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:38:19 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/ui/hud.h"
#include "../../includes/game/g_axis.h"

static void	score_hud(t_shaders *sh)
{
	t_shaders	*fr;
	t_area		*ar;
	t_screen	*scr;
	t_player	*user;
	char		*buffer;

	fr = get_img("/hud_score.xpm");
	scr = get_screen();
	user = get_user();
	if (user && scr && fr && sh)
	{
		ar = &scr->area;
		buffer = xitoa(user->score);
		if (buffer)
		{
			merge_img(sh, fr, (t_vec2){ar->a1.x, ar->a4.y - 194});
			typewritter("framework", buffer, \
			(t_vec2){ar->a1.x + 2, ar->a4.y - 192});
			xfree((void **)&buffer);
			display_perks(sh, ar->a1.x, ar->a4.y - 154);
		}
	}
}

static void	weapon_hud(t_shaders *sh)
{
	t_screen	*screen;
	t_player	*player;
	t_area		*ar;

	screen = get_screen();
	player = get_user();
	if (screen && player)
	{
		ar = &screen->area;
		merge_img(sh, get_img("/dpad_bar.xpm"),
			(t_vec2){ar->a3.x - 306, ar->a3.y - 116});
		merge_img(sh, get_img("/dpad.xpm"),
			(t_vec2){ar->a3.x - 110, ar->a3.y - 205});
		get_weapon_info();
		typewritter("framework", player->weapon->info_buffer,
			(t_vec2){ar->a3.x - 200, ar->a3.y - 168});
	}
}

static void	crosshair_hud(t_shaders *sh)
{
	t_shaders	*cv;
	t_shaders	*ch;
	t_player	*user;
	int			v;

	user = get_user();
	if (user)
	{
		cv = get_img("/crosshair_v.xpm");
		ch = get_img("/crosshair_h.xpm");
		v = (user->velocity * 8);
		if (ch && cv && sh)
		{
			merge_img(sh, cv, (t_vec2){638, 347 - v});
			merge_img(sh, cv, (t_vec2){638, 363 + v});
			merge_img(sh, ch, (t_vec2){627 - v, 358});
			merge_img(sh, ch, (t_vec2){643 + v, 358});
		}
	}
}

void	hud_render(void)
{
	t_shaders	*sh;

	sh = get_tex(TEX_RENDER);
	if (sh)
	{
		weapon_hud(sh);
		score_hud(sh);
		health_bar(sh);
		hitmarker();
		crosshair_hud(sh);
		display_round();
	}
}
