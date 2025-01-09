/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_add_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:58:06 by lchiva            #+#    #+#             */
/*   Updated: 2024/05/28 06:15:59 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	make_wall(t_core *core, int c, void (*f)(), char *name)
{
	t_vec2	null;

	null = vec2t(0, 0);
	create_img(core, ui_add(null, vec2t(60, 60), c), f, name);
}

static void	compile_imgx(t_core *core, char *str1, char *str2, char *str3)
{
	compile_img(get_img(core, str1), get_img(core, str2), get_img(core, str3));
}

void	add_wall_img(t_core *core)
{
	make_wall(core, 0x5F5F5F, wall_left, "/wall_left");
	make_wall(core, 0x5F5F5F, wall_right, "/wall_right");
	make_wall(core, 0x5F5F5F, wall_top, "/wall_up");
	make_wall(core, 0x5F5F5F, wall_bottom, "/wall_down");
	make_wall(core, 0, NULL, "/wall_rock");
	compile_imgx(core, "/wall_rock", "/ground.xpm", "/rock.xpm");
}
