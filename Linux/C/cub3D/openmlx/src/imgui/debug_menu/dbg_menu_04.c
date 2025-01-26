/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_menu_04.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:53:02 by lchiva            #+#    #+#             */
/*   Updated: 2024/10/24 00:00:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static double	recaster_type(__uint8_t type, void *_var)
{
	if (type == OPT_INT)
		return (*(int *)_var);
	else if (type == OPT_FLOAT)
		return (*(float *)_var);
	else if (type == OPT_DOUBLE)
		return (*(double *)_var);
	else if (type == OPT_LONG)
		return (*(long *)_var);
	else if (type == OPT_SHORT)
		return (*(short *)_var);
	else if (type == OPT_CHAR)
		return (*(char *)_var);
	return (0);
}

void	dbg_draw_slider(t_menu *menu, t_opt *o, size_t i)
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
	v = recaster_type(o->_type, o->_var);
	s = ml_quad((t_vec2){141, a}, (t_vec2){(int)linear_scaling(v, o->_min,
				o->_max, 148), 8}, menu->_color);
	ml_savemesh(&s, "imgui_dbg_menu");
	ml_end(&s);
}
