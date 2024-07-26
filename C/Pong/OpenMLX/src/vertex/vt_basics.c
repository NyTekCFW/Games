/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_basics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:30:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 02:58:48 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief create a temporary primitive,
///initialise all settings depending
//of the type of primitive and return it
/// @param prim primitive type e.g : ML_PRIM_QUADS
/// @return 
t_prim	ml_begin(int prim)
{
	t_prim	tmp;

	xmemset(&tmp, 0, sizeof(t_prim));
	tmp.primitive = prim;
	tmp.size = 1;
	tmp.intensity = 1.0f;
	if (prim != ML_PRIM_LINE_LOOP && prim != ML_PRIM_LINE_STRIP)
		tmp.mode = ML_MODE_FILL;
	else
		tmp.mode = ML_MODE_LINE;
	return (tmp);
}

/// @brief add a vertex position (x, y)
///into the current primitive 's',
/// with a maximum of 360 vertex position
/// @param s current primitive
/// @param origin position
void	ml_vertex(t_prim *s, t_vec2 origin)
{
	if (s->cpoint < 360)
	{
		s->point[s->cpoint] = origin;
		s->cpoint++;
	}
}

/// @brief set a color into the current primitive
///s, work also to set a color on a shader
/// @param s current primitive
/// @param color color
void	ml_color(t_prim *s, __uint32_t color)
{
	if (s->texture == ML_TEXTURE_IMG)
		s->color_texture = color;
	else
		s->color = color;
}

/// @brief set a render size of the current
/// primitive, e.g : if its a primitive line,
/// the line width will be set by the size
/// @param s current primitive
/// @param size size / width 
void	ml_size(t_prim *s, __uint32_t size)
{
	s->size = size;
}

/// @brief call the render type of
///the current primitive type and
///check that the min requiered
///to do the render is respected
/// @param s current primitive
void	ml_end(t_prim *s)
{
	if (s->primitive == ML_PRIM_POINTS && s->cpoint == 1 && s->size > 0)
		ml_draw_points(s);
	else if (s->primitive == ML_PRIM_LINES && s->cpoint == 2)
		ml_draw_lines(s, 0, 1);
	else if ((s->primitive == ML_PRIM_LINE_LOOP && s->cpoint >= 2)
		|| (s->primitive == ML_PRIM_LINE_STRIP && s->cpoint >= 2))
		ml_draw_line_sl(s);
	else if (s->primitive == ML_PRIM_TRIANGLES && s->cpoint == 3)
		ml_draw_triangles(s);
	else if (s->primitive == ML_PRIM_QUADS && s->cpoint == 4)
		ml_draw_quads(s);
	else if (s->primitive == ML_PRIM_POLYGON && s->cpoint >= 3)
		ml_draw_polygon(s);
	else if (s->primitive == ML_PRIM_QUAD_STRIP
		&& s->cpoint >= 4 && (s->cpoint % 4) == 0)
		ml_draw_quad_strip(s);
}
