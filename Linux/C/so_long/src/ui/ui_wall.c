/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:15:27 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/19 07:02:07 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	wall_left(t_img *img, t_ui ui)
{
	__uint32_t	clr;
	t_vec2		xy;

	xy = vec2t(-1, -1);
	while (++xy.y < ui.h)
	{
		xy.x = -1;
		while (++xy.x < ui.w)
		{
			if (xy.x < ui.w - 5 || xy.y % 5 == 0)
				clr = 0;
			else
				clr = ui.color;
			set_color(img, get_px_adr(img, xy), clr);
		}
	}
}

void	wall_bottom(t_img *img, t_ui ui)
{
	__uint32_t	clr;
	t_vec2		xy;

	xy = vec2t(-1, -1);
	while (++xy.y < ui.h)
	{
		xy.x = -1;
		while (++xy.x < ui.w)
		{
			if (xy.x % 6 == 0 || xy.y > 5)
				clr = 0;
			else
				clr = ui.color;
			set_color(img, get_px_adr(img, xy), clr);
		}
	}
}

void	wall_right(t_img *img, t_ui ui)
{
	__uint32_t	clr;
	t_vec2		xy;

	xy = vec2t(-1, -1);
	while (++xy.y < ui.h)
	{
		xy.x = -1;
		while (++xy.x < ui.w)
		{
			if (xy.x > 5 || xy.y % 5 == 0)
				clr = 0;
			else
				clr = ui.color;
			set_color(img, get_px_adr(img, xy), clr);
		}
	}
}

void	wall_top(t_img *img, t_ui ui)
{
	__uint32_t	clr;
	t_vec2		xy;

	xy = vec2t(-1, -1);
	while (++xy.y < ui.h)
	{
		xy.x = -1;
		while (++xy.x < ui.w)
		{
			if (xy.y < ui.h - 6 || (xy.x > 0 && xy.x % 6 == 0))
				clr = 0;
			else
				clr = ui.color;
			set_color(img, get_px_adr(img, xy), clr);
		}
	}
}
