/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:06:46 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/11 09:26:26 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	r_centertext(t_core *core, t_ui ui, char *str)
{
	int		w;
	t_vec2	ui_text;

	w = r_textwidth(str);
	ui_text.x = ui.x + (w / 2) - (w / 4);
	ui_text.y = ui.y + (ui.h / 2) + (ui.h / 4);
	r_drawtext(core, &ui_text, get_color(core)->white, str);
}

void	r_line(t_core *core, t_ln *ui)
{
	int		i;
	t_vec2	dxy;
	int		steps;
	t_vec2f	xy_inc;
	t_vec2f	xy;

	i = 0;
	dxy = vec2t(ui->x2 - ui->x1, ui->y2 - ui->y1);
	steps = abs(dxy.y);
	if (abs(dxy.x) > abs(dxy.y))
		steps = abs(dxy.x);
	xy_inc.x = (float)dxy.x / (float)steps;
	xy_inc.y = (float)dxy.y / (float)steps;
	dxy = vec2t(ui->x1, ui->y1);
	xy.x = ui->x1;
	xy.y = ui->y1;
	while (i++ < steps)
	{
		r_drawpix(core, &dxy, ui->color);
		xy.x += xy_inc.x;
		xy.y += xy_inc.y;
		dxy = vec2t(xy.x, xy.y);
	}
}

t_ln	ln_add(t_vec2 xy1, t_vec2 xy2, __uint32_t color)
{
	t_ln	new;

	new.x1 = xy1.x;
	new.y1 = xy1.y;
	new.x2 = xy2.x;
	new.y2 = xy2.y;
	new.color = color;
	return (new);
}

t_ui	ui_add(t_vec2 xy, t_vec2 wh, __uint32_t clr)
{
	t_ui	gnew;

	gnew.color = clr;
	gnew.x = xy.x;
	gnew.y = xy.y;
	gnew.w = wh.x;
	gnew.h = wh.y;
	return (gnew);
}
