/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_color_picker_00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:07:26 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:15:45 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

void	cpicker_init(t_ml *lx)
{
	register_exp_img("cpicker_bar");
	register_exp_img("cpicker_bkg");
	register_exp_img("cpicker_cursor");
	create_img((t_ui){290, 345, 0}, fill_img_color, "cpicker_render");
	create_img((t_ui){25, 25, 0}, fill_img_color, "cpicker_obox");
	create_img((t_ui){25, 25, 0}, fill_img_color, "cpicker_nbox");
	create_img((t_ui){15, 15, 0}, fill_img_color, "cpicker_bar_cursor");
	create_img((t_ui){15, 15, 0}, fill_img_color, "cpicker_grd_cursor");
	create_img((t_ui){255, 255, 0}, fill_img_color,
		"cpiker_gradient");
	lx->cpicker.u = (t_vec2){0, 0};
	lx->cpicker.cursor = (t_vec2){0};
	lx->cpicker.cursor_bar = (t_vec2){0, 277};
	lx->cpicker.is_open = 0;
	lx->cpicker.c_color = NULL;
	lx->cpicker.init_color = 0;
	lx->cpicker.new_color = 0xFFFFFF;
	lx->cpicker.bar_color = 0x030303;
	lx->cpicker.grd = (t_vec2){252, 250};
	lx->cpicker.bar = (t_vec2){255, 10};
}

void	cpicker_moveto(t_vec2 v)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
		lx->cpicker.u = v;
}

void	cpicker_edit(__uint32_t *c)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && c && !lx->cpicker.is_open
		&& !lx->cpicker.c_color)
		lx->cpicker.c_color = c;
}

void	cpicker_open(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && !lx->cpicker.is_open && lx->cpicker.c_color)
	{
		lx->cpicker.is_open = 1;
		lx->cpicker.init_color = *lx->cpicker.c_color;
	}
}
