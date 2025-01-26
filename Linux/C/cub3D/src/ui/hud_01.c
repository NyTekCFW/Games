/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:50:28 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:15:00 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_axis.h"

static __uint32_t	health_color(t_player *user, int maxhealth)
{
	float	ratio;
	int		red;
	int		green;

	ratio = (float)user->health / (float)maxhealth;
	red = (int)((1.0f - ratio) * 255);
	green = (int)(ratio * 255);
	return ((red << 16) | (green << 8) | 0x00);
}

static void	health_bar_p(t_area *ar, t_player *user, t_shaders *sh)
{
	t_prim		p;
	int			health;
	int			o;

	o = has_perk(PERK_JUGGERNOG);
	health = (int)linear_scaling(user->health, 0, 150 * (1 + o), 130);
	p = ml_begin(ML_PRIM_QUADS);
	_health_loc(&p, ar, user, health);
	ml_color(&p, health_color(user, 150 * (1 + o)));
	ml_savemesh(&p, sh->img_name);
	ml_overwrite(&p, 0);
	ml_end(&p);
}

static void	_health_loc_bkg(t_prim *p, t_area *ar, t_player *user)
{
	t_axis	*zm;
	int		o;

	zm = get_zm();
	o = has_perk(PERK_JUGGERNOG);
	if ((zm && zm->alive) || user->health < (150 * (1 + o)))
	{
		ml_vertex(p, (t_vec2){466, 357});
		ml_vertex(p, (t_vec2){466 + 142, 357});
		ml_vertex(p, (t_vec2){466 + 142, 364});
		ml_vertex(p, (t_vec2){466, 364});
	}
	else
	{
		ml_vertex(p, (t_vec2){ar->a1.x, ar->a4.y - 205});
		ml_vertex(p, (t_vec2){ar->a1.x + 142, ar->a4.y - 205});
		ml_vertex(p, (t_vec2){ar->a1.x + 142, ar->a4.y - 198});
		ml_vertex(p, (t_vec2){ar->a1.x, ar->a4.y - 198});
	}
}

void	health_bar(t_shaders *sh)
{
	t_prim		p;
	t_area		*ar;
	t_player	*user;
	t_screen	*scr;

	scr = get_screen();
	user = get_user();
	if (scr && user)
	{
		ar = &scr->area;
		p = ml_begin(ML_PRIM_QUADS);
		_health_loc_bkg(&p, ar, user);
		ml_color(&p, 0x030303);
		ml_savemesh(&p, sh->img_name);
		ml_overwrite(&p, 0);
		ml_end(&p);
		health_bar_p(ar, user, sh);
	}
}

void	display_perks(t_shaders *sh, int x, int y)
{
	t_player	*user;
	int			i;
	int			u;
	char		buffer[10];

	user = get_user();
	i = PERK_QUICKREGEN;
	u = 0;
	if (user && sh)
	{
		while (i < 9)
		{
			if ((user->perks & i))
			{
				xstrcpy(buffer, "perks_000");
				buffer[8] = u + 0x30;
				merge_img(sh, get_img(buffer), (t_vec2){x, y});
				x += 35;
			}
			++u;
			i *= 2;
		}
	}
}
