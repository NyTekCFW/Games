/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:42:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/06 23:34:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	add_local_anim(t_core *core)
{
	add_img(core, "textures/player/b_pimg.xpm");
	add_img(core, "textures/player/f_pimg.xpm");
	add_img(core, "textures/player/l_pimg.xpm");
	add_img(core, "textures/player/r_pimg.xpm");
	add_img(core, "textures/axis.xpm");
	add_img(core, "textures/fire.xpm");
	add_img(core, "textures/exit.xpm");
}

void	add_local_img(t_core *core)
{
	t_account	*acc;

	acc = get_account(core);
	if (acc->reso == r_480p)
		add_img(core, "textures/bkg/480p/intro.xpm");
	if (acc->reso == r_720p)
		add_img(core, "textures/bkg/720p/intro.xpm");
	if (acc->reso == r_1080p)
		add_img(core, "textures/bkg/1080p/intro.xpm");
	if (acc->reso == r_1440p)
		add_img(core, "textures/bkg/1440p/intro.xpm");
	if (acc->reso == r_2160p)
		add_img(core, "textures/bkg/2160p/intro.xpm");
	add_img(core, "textures/ground.xpm");
	add_img(core, "textures/ground_p.xpm");
	add_img(core, "textures/rock.xpm");
	add_img(core, "textures/rupies.xpm");
	add_local_anim(core);
}

void	add_ui_img(t_core *core)
{
	t_color	*clr;
	t_vec2	null;

	null = vec2t(0, 0);
	clr = get_color(core);
	create_img(core, ui_add(null, vec2t(60, 60), 0),
		NULL, "/ui_rupies");
	create_img(core, ui_add(null, vec2t(1, 1), 0),
		NULL, "/ui_line");
	create_img(core, ui_add(null, vec2t(100, 20),
			clr->grey), r_draw_box, "/ui_button");
	create_img(core, ui_add(null, vec2t(196, 122),
			clr->grey), r_draw_box, "/ui_leaderboard");
	create_img(core, ui_add(null, vec2t(115, 77),
			clr->grey), r_draw_box, "/ui_info");
	create_img(core, ui_add(null, vec2t(218, 96),
			clr->grey), r_draw_box, "/ui_pause");
	create_img(core, ui_add(null, vec2t(218, 16),
			clr->grey), r_draw_box, "/ui_pause_bar");
	create_img(core, ui_add(null, vec2t(88, 116),
			clr->grey), r_draw_box, "/ui_pause_cmd");
}
