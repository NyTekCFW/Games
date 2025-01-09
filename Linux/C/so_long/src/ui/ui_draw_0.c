/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:40:13 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/16 20:55:02 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	r_draw_box(t_img *img, t_ui ui)
{
	__uint32_t	clr;
	t_vec2		xy;

	xy = vec2t(-1, -1);
	while (++xy.y < ui.h)
	{
		xy.x = -1;
		while (++xy.x < ui.w)
		{
			if (xy.y == 0 || xy.y == ui.h - 1 || xy.x == 0 || xy.x == ui.w - 1)
				clr = 0xFFFFFF;
			else
				clr = ui.color;
			if (xy.y >= 1 && xy.y <= ui.h - 2)
			{
				if (xy.x == 1 || xy.x == ui.w - 2
					|| (xy.x >= 1 && xy.x <= ui.w - 2 && xy.y == 1)
					|| (xy.x >= 1 && xy.x <= ui.w - 2 && xy.y == ui.h - 2))
					clr = 0;
			}
			set_color(img, get_px_adr(img, xy), clr);
		}
	}
}

int	r_textwidth(char *str)
{
	int	width;

	width = 0;
	while (*str++)
		width += 7;
	return (width);
}

void	r_drawpix(t_core *core, t_vec2 *px, __uint32_t clr)
{
	t_imgx	*imgx;

	imgx = get_img(core, "/ui_line");
	set_color(&imgx->img, get_px_adr(&imgx->img, vec2t(0, 0)), clr);
	print_img(core, *px, "/ui_line");
}

void	r_drawtext(t_core *core, t_vec2 *xy, __uint32_t c, char *s)
{
	mlx_string_put(core->mlx.ptr, core->mlx.win, xy->x + 1,
		xy->y - 1, 0, s);
	mlx_string_put(core->mlx.ptr, core->mlx.win, xy->x,
		xy->y, c, s);
	xy->y += 20;
}

void	r_draw_wall(t_core *core, t_ui ui)
{
	t_vec2	num;
	t_vec2	xy;
	t_vec2	max;
	t_game	*gm;

	gm = get_game(core);
	max = vec2t(gm->map_max.x - 1, gm->map_max.y - 1);
	if (get_client(core)->zones.x > 0 || get_client(core)->zones.y > 0)
		max = vec2t(max.x - gm->map_rng.x,
				max.y - gm->map_rng.y);
	xy = vec2t(ui.x, ui.y);
	num = get_ent_pos(core, ui);
	printwallx(core, xy, num, max);
}
