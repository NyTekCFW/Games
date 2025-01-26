/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_menu_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:36:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/10/22 20:25:13 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

void	dbg_upd_size(int w, int h)
{
	fill_shader_color("imgui_dbg_menu", 0);
	resize_img("imgui_dbg_menu", w, h);
}

void	dbg_string(t_ml *lx, int x, int y, char *name)
{
	if (lx && lx->ptr && lx->win && name
		&& x >= 0 && x < lx->width
		&& y >= 0 && y < lx->height)
	{
		mlx_string_put(lx->ptr, lx->win, x + 1, y, 0x030303, name);
		mlx_string_put(lx->ptr, lx->win, x, y, 0xFFFFFF, name);
	}
}

static void	fix_overflow(double *is, __uint8_t type)
{
	t_vec2f	mm;

	mm = (t_vec2f){0};
	if (type == OPT_LONG)
		mm = (t_vec2f){(double)-0x7FFFFFFFFFFFFDFF, (double)0x7FFFFFFFFFFFFDFF};
	else if (type == OPT_CHAR)
		mm = (t_vec2f){(double)(-128), (double)(127)};
	else if (type == OPT_SHORT)
		mm = (t_vec2f){(double)(-32768), (double)(32767)};
	else if (type == OPT_INT)
		mm = (t_vec2f){(double)(-2147483648), (double)(2147483647)};
	else
		return ;
	if (*is < mm.x)
		*is = mm.x;
	else if (*is > mm.y)
		*is = mm.y;
}

void	apply_click(t_opt *opt, t_vec2 u)
{
	double	is;

	if (opt->_type == OPT_BOOL)
		*(int *)opt->_var = !*(int *)opt->_var;
	else
	{
		is = inverse_scaling(u.x - opt->range.x, opt->_min, opt->_max, 148);
		fix_overflow(&is, opt->_type);
		if (opt->_type == OPT_LONG)
			*(long *)opt->_var = (long)is;
		else if (opt->_type == OPT_INT)
			*(int *)opt->_var = (int)is;
		else if (opt->_type == OPT_FLOAT)
			*(float *)opt->_var = (float)is;
		else if (opt->_type == OPT_DOUBLE)
			*(double *)opt->_var = is;
		else if (opt->_type == OPT_SHORT)
			*(short *)opt->_var = (short)is;
		else if (opt->_type == OPT_CHAR)
			*(char *)opt->_var = (char)is;
	}
}

void	dbg_click(t_vec2 u)
{
	t_menu	*menu;
	t_opt	*opt;
	size_t	i;

	menu = dbg_menu(ACT_GET);
	if (menu)
	{
		i = 0;
		while (i < menu->_opts_count && i < 128)
		{
			opt = &menu->_options[i];
			if (is_in_range((t_vec2){opt->range.x, opt->range.y},
				u, (t_vec2){opt->range.z, opt->range.w}))
				apply_click(opt, u);
			i++;
		}
	}
}
