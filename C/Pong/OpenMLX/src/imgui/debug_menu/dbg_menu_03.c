/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_menu_03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:34:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:17:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static void	draw_slider(t_menu *menu, t_opt *o, size_t i)
{
	t_prim	s;
	int		a;
	double	v;

	s = (t_prim){0};
	v = 0;
	a = 28 + (menu->_spacing * i);
	if (o->_type == OPT_BOOL || o->_type == OPT_PTR
		|| o->_type == OPT_STR)
		return ;
	if (o->_type == OPT_INT)
		v = *(int *)o->_var;
	else if (o->_type == OPT_FLOAT)
		v = *(float *)o->_var;
	else if (o->_type == OPT_LONG)
		v = *(long *)o->_var;
	else if (o->_type == OPT_SHORT)
		v = *(short *)o->_var;
	else if (o->_type == OPT_CHAR)
		v = *(char *)o->_var;
	s = ml_quad((t_vec2){141, a}, (t_vec2){(int)linear_scaling(v, o->_min,
				o->_max, 148), 8}, menu->_color);
	ml_savemesh(&s, "imgui_dbg_menu");
	ml_end(&s);
}

static void	draw_icon(t_menu *menu, t_opt *opt, int i)
{
	t_prim	s;

	s = (t_prim){0};
	if (opt->_type == OPT_BOOL && opt->_var && *(int *)opt->_var)
	{
		s = ml_quad((t_vec2){141, 28 + (menu->_spacing * i)},
				(t_vec2){8, 8}, menu->_color);
		ml_savemesh(&s, "imgui_dbg_menu");
		ml_end(&s);
	}
	else if (opt->_var && opt->_type != OPT_PTR && opt->_type != OPT_STR)
		draw_slider(menu, opt, i);
}

static void	draw_icon_opts(t_menu *menu, size_t i)
{
	t_opt	*opt;
	t_prim	s;
	int		w;

	s = (t_prim){0};
	if (menu)
	{
		opt = &menu->_options[i];
		if (opt)
		{
			if (opt->_type == OPT_STR || opt->_type == OPT_PTR)
				return ;
			w = 10;
			if (opt->_type != OPT_BOOL)
				w = 150;
			s = ml_quad((t_vec2){140, 27 + (menu->_spacing * i)},
					(t_vec2){w, 10}, 0xFFFFFF);
			ml_savemesh(&s, "imgui_dbg_menu");
			ml_end(&s);
			draw_icon(menu, opt, i);
		}
	}
}

static void	draw_design(t_menu *m)
{
	t_prim	s;

	s = ml_quad((t_vec2){0}, (t_vec2){m->_width, 20}, m->_color);
	ml_savemesh(&s, "imgui_dbg_menu");
	ml_end(&s);
	s = ml_quad((t_vec2){0, 20}, (t_vec2){m->_width, m->_height}, 0x151617);
	ml_savemesh(&s, "imgui_dbg_menu");
	ml_end(&s);
	s = ml_triangle((t_vec2){5, 6}, (t_vec2){15, 6},
			(t_vec2){10, 14}, 0xFFFFFF);
	ml_savemesh(&s, "imgui_dbg_menu");
	ml_end(&s);
}

void	dbg_display_menu(t_ml *lx)
{
	t_menu	*menu;
	size_t	i;

	menu = dbg_menu(ACT_GET);
	i = 0;
	if (lx && menu)
	{
		menu->_width = 560 + menu->_scaling.x;
		menu->_height = 24 + (menu->_spacing * menu->_opts_count)
			+ menu->_scaling.y;
		dbg_upd_size(menu->_width, menu->_height);
		draw_design(menu);
		while (i < menu->_opts_count && i < 128)
			draw_icon_opts(menu, i++);
		dbg_draw_options(lx, menu);
	}
}
