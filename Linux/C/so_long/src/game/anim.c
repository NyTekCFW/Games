/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:54:50 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/16 21:30:43 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	register_anim(t_core *core, int anim, t_vec2 info, char *name)
{
	t_anim	*gm;

	gm = get_anim(core);
	gm->status[anim] = 0;
	gm->max_status[anim] = info.x;
	gm->rate[anim] = info.y;
	gm->frame[anim] = clock() + gm->rate[anim];
	insert_str(gm->name[anim], name, 32);
}

void	next_anim(t_core *core, int anim)
{
	size_t	size;
	t_anim	*gm;

	gm = get_anim(core);
	gm->frame[anim] = clock() + gm->rate[anim];
	gm->status[anim]++;
	if (gm->status[anim] >= gm->max_status[anim])
		gm->status[anim] = 0;
	size = sl_strlen(gm->name[anim]) - 1;
	gm->name[anim][size] = 0x30 + gm->status[anim];
}

void	check_anim(t_core *core)
{
	t_anim	*gm;

	gm = get_anim(core);
	if (clock() >= gm->frame[a_fire])
		next_anim(core, a_fire);
	if (clock() >= gm->frame[a_player])
		next_anim(core, a_player);
	if (get_client(core)->is_meleeing && clock() >= gm->frame[a_player_melee])
		get_client(core)->is_meleeing = 0;
	if (clock() >= gm->frame[a_axis])
	{
		next_anim(core, a_axis);
		if (gm->status[a_axis] == 0)
			browse_map(core, a_move);
	}
	if (clock() >= gm->frame[a_exit] && get_game(core)->ents[c_collect] == 0
		&& gm->status[a_exit] < 3)
		next_anim(core, a_exit);
	if (clock() >= gm->frame[f_timer])
	{
		fade_rgb(core);
		rupee_render(core, get_img(core, "/ui_rupies"),
			get_img(core, "/ground.xpm"), get_img(core, "/rupies.xpm"));
		gm->frame[f_timer] = clock() + 160000;
	}
}

void	init_anim(t_core *core)
{
	register_anim(core, a_fire, vec2t(2, 130000), "/fire_0");
	register_anim(core, a_player, vec2t(2, 250000), "/player_0");
	register_anim(core, a_player_melee, vec2t(1, 100000), "/player_2");
	register_anim(core, a_axis, vec2t(5, 150000), "/axis_0");
	register_anim(core, a_exit, vec2t(4, 800000), "/exit_0");
}
