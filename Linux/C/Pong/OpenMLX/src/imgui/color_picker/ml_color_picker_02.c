/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_color_picker_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:11:26 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:15:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static int	_check(void)
{
	t_shaders	*s;
	char		*str[7];
	int			i;

	i = -1;
	str[0] = "cpicker_bkg";
	str[1] = "cpiker_gradient";
	str[2] = "cpicker_grd_cursor";
	str[3] = "cpicker_bar_cursor";
	str[4] = "cpicker_obox";
	str[5] = "cpicker_nbox";
	str[6] = "cpicker_render";
	while (++i < 7 && str[i])
	{
		s = get_img(str[i]);
		if (!s)
			return (0);
	}
	return (1);
}

static void	_asm_img(t_shaders *sh, char *name, t_vec2 u)
{
	t_shaders	*de;

	if (sh && name)
	{
		de = get_img(name);
		if (de)
			merge_img(sh, de, u);
	}
}

static void	_asm_render(t_shaders *sh, char *name, t_vec2 u)
{
	t_shaders	*de;

	if (sh && name)
	{
		de = get_img(name);
		if (de)
			merge_img(de, sh, u);
	}
}

static void	_build(t_shaders *sh, t_ml *lx, char *merge_to)
{
	if (sh && lx)
	{
		_asm_img(sh, "cpicker_bkg", (t_vec2){0});
		_asm_img(sh, "cpiker_gradient", (t_vec2){10, 20});
		_asm_img(sh, "cpicker_grd_cursor", (t_vec2){8 + lx->cpicker.cursor.x,
			17 + lx->cpicker.cursor.y});
		_asm_img(sh, "cpicker_bar", (t_vec2){10, 280});
		_asm_img(sh, "cpicker_bar_cursor", (t_vec2){8
			+ lx->cpicker.cursor_bar.x, 277});
		_asm_img(sh, "cpicker_obox", (t_vec2){10, 295});
		_asm_img(sh, "cpicker_nbox", (t_vec2){48, 295});
		if (merge_to && merge_to[0])
			_asm_render(sh, merge_to, lx->cpicker.u);
		else
			print_img(lx->cpicker.u, "cpicker_render");
	}
}

/// @brief display color picker at
///lx->cpicker.u position, the color
///picker can be print directly or merge
///to another image
/// @param lx //gmlx struct
/// @param merge_to //NULL to print directly
///"/<image>.xpm" to merge on another image
void	cpicker_show(t_ml *lx, char *merge_to)
{
	static int	v = -1;
	t_shaders	*sh;

	if (v == -1)
		v = _check();
	if (lx && v)
	{
		cpicker_grad(lx);
		cpicker_cursor_bar("cpicker_bar_cursor", lx->cpicker.cursor_bar,
			&lx->cpicker.bar_color);
		cpicker_cursor("cpicker_grd_cursor", lx->cpicker.new_color);
		fill_shader_color("cpicker_obox", lx->cpicker.init_color);
		fill_shader_color("cpicker_nbox", lx->cpicker.new_color);
		*lx->cpicker.c_color = lx->cpicker.new_color;
		sh = get_img("cpicker_render");
		if (sh)
			_build(sh, lx, merge_to);
	}
}
