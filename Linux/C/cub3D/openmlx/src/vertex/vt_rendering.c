/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:33:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 03:04:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	lines_input(t_prim *s, t_vec2 data)
{
	t_vec4	v;

	if (ml_can_draw(s, data))
	{
		if (s->savemesh)
		{
			v = (t_vec4){0, data.x, 0, data.y};
			if (!s->overwrite)
				ml_overwrite_fix(s, &v);
			set_color(s->savemesh, get_px_adr(s->savemesh,
					(t_vec2){v.y, v.w}), s->color);
		}
		else
			ml_put_pixel(data.x, data.y, s->color);
	}
}

/// @brief render function for
///points primitive
/// @param s current primitive
void	ml_draw_points(t_prim *s)
{
	t_vec2		p;
	t_vec2		m[2];
	int			i;

	i = s->size / 2;
	m[0] = (t_vec2){s->point[0].x - i, s->point[0].y - i};
	m[1] = (t_vec2){s->point[0].x + i, s->point[0].y + i};
	p.y = m[0].y;
	while (p.y < m[1].y)
	{
		p.x = m[0].x;
		while (p.x < m[1].x)
		{
			if (s->savemesh)
				lines_input(s, p);
			else if (ml_can_draw(s, p))
				ml_put_pixel(p.x, p.y, s->color);
			p.x++;
		}
		p.y++;
	}
}

static void	lines_render(t_prim *s, double imz[], t_vec2 p[], double d[])
{
	t_vec2	data;
	double	per[2];
	double	length;

	length = sqrt(d[0] * d[0] + d[1] * d[1]);
	per[0] = -d[1] / length;
	per[1] = d[0] / length;
	imz[2] = 0;
	while (imz[2] < imz[1])
	{
		data = (t_vec2){(p[0].x + imz[0] * d[0] + imz[2] * per[0]),
			(p[0].y + imz[0] * d[1] + imz[2] * per[1])};
		lines_input(s, data);
		data = (t_vec2){(p[0].x + imz[0] * d[0] - imz[2] * per[0]),
			(p[0].y + imz[0] * d[1] - imz[2] * per[1])};
		lines_input(s, data);
		imz[2] += 0.01;
	}
	if (!imz[1])
	{
		data = (t_vec2){(p[0].x + imz[0] * d[0]), (p[0].y + imz[0] * d[1])};
		lines_input(s, data);
	}
}

/// @brief render function for
///lines primitive
/// @param s current primitive
void	ml_draw_lines(t_prim *s, int w, int e)
{
	double	d[2];
	t_vec2	p[2];
	double	length;
	double	imz[3];

	xmemcpy(imz, (double []){0.0, s->size / 2, 0.0}, sizeof(imz));
	if (s->size == 1)
		imz[1] = 0;
	p[0] = (t_vec2){s->point[w].x, s->point[w].y};
	p[1] = (t_vec2){s->point[e].x, s->point[e].y};
	d[0] = p[1].x - p[0].x;
	d[1] = p[1].y - p[0].y;
	length = sqrt(d[0] * d[0] + d[1] * d[1]);
	while (imz[0] < 1.0)
	{
		lines_render(s, imz, p, d);
		imz[0] += 1.0 / length;
	}
}
