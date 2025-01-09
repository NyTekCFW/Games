/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_add_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:57:30 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/06 23:35:19 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	make_anim_img(t_core *core, int frame, t_vec2 dim, char *name)
{
	t_vec2	null;
	int		frm;
	char	tmp[32];

	insert_str(tmp, name, 32);
	null = vec2t(0, 0);
	frm = 0;
	while (frm < frame + 1)
	{
		tmp[sl_strlen(tmp) - 1] = 0x30 + frm;
		create_img(core, ui_add(null, dim, 0), NULL, tmp);
		frm++;
	}
}

static void	compile_imgx(t_core *core, char *str1, char *str2, char *str3)
{
	compile_img(get_img(core, str1), get_img(core, str2), get_img(core, str3));
}

static void	filled_anim(t_core *core)
{
	rupee_render(core, get_img(core, "/ui_rupies"),
		get_img(core, "/ground.xpm"), get_img(core, "/rupies.xpm"));
	compile_imgx(core, "/player_0", "/ground_p.xpm", "/player_0");
	compile_imgx(core, "/player_1", "/ground_p.xpm", "/player_1");
	compile_imgx(core, "/player_2", "/ground_p.xpm", "/player_2");
	compile_imgx(core, "/fire_0", "/ground.xpm", "/fire_0");
	compile_imgx(core, "/fire_1", "/ground.xpm", "/fire_1");
	compile_imgx(core, "/exit_0", "/ground.xpm", "/exit_0");
	compile_imgx(core, "/exit_1", "/ground.xpm", "/exit_1");
	compile_imgx(core, "/exit_2", "/ground.xpm", "/exit_2");
	compile_imgx(core, "/exit_3", "/ground.xpm", "/exit_3");
	compile_imgx(core, "/axis_0", "/ground.xpm", "/axis_0");
	compile_imgx(core, "/axis_1", "/ground.xpm", "/axis_1");
	compile_imgx(core, "/axis_2", "/ground.xpm", "/axis_2");
	compile_imgx(core, "/axis_3", "/ground.xpm", "/axis_3");
	compile_imgx(core, "/axis_4", "/ground.xpm", "/axis_4");
}

void	change_pview(t_core *core, char d)
{
	char	tmp[32];

	insert_str(tmp, "/f_pimg.xpm", 32);
	tmp[1] = d;
	split_asset(core, vec3t(40, 40, 2), (char *[]){tmp, "/player_0"});
	compile_imgx(core, "/player_0", "/ground_p.xpm", "/player_0");
	compile_imgx(core, "/player_1", "/ground_p.xpm", "/player_1");
	compile_imgx(core, "/player_2", "/ground_p.xpm", "/player_2");
}

void	add_img_anim(t_core *core)
{
	make_anim_img(core, 2, vec2t(40, 40), "/player_0");
	make_anim_img(core, 3, vec2t(60, 60), "/exit_0");
	make_anim_img(core, 4, vec2t(60, 60), "/axis_0");
	make_anim_img(core, 1, vec2t(60, 60), "/fire_0");
	split_asset(core, vec3t(60, 60, 4), (char *[]){"/axis.xpm", "/axis_0"});
	split_asset(core, vec3t(60, 60, 1), (char *[]){"/fire.xpm", "/fire_0"});
	split_asset(core, vec3t(60, 60, 3), (char *[]){"/exit.xpm", "/exit_0"});
	split_asset(core, vec3t(40, 40, 2), (char *[]){"/f_pimg.xpm", "/player_0"});
	filled_anim(core);
}
