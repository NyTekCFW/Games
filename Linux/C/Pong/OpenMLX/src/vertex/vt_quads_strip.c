/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_quads_strip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:45:18 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 03:03:13 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	ml_quad_settings(t_prim *d, t_prim *b)
{
	ml_color(d, b->color);
	ml_setmode(d, b->mode);
	ml_size(d, b->size);
	d->savemesh = b->savemesh;
	if (b->texture != ML_TEXTURE_NONE)
	{
		d->texture = b->texture;
		d->img = b->img;
		d->color_texture = b->color_texture;
		d->intensity = b->intensity;
		d->overwrite = b->overwrite;
	}
}

/// @brief render for quad strip
/// primitive
/// @param s current primitive
void	ml_draw_quad_strip(t_prim *s)
{
	int		i;
	t_prim	quad;

	i = 0;
	while (i < s->cpoint - 3)
	{
		quad = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&quad, s->point[i]);
		ml_vertex(&quad, s->point[i + 1]);
		ml_vertex(&quad, s->point[i + 2]);
		ml_vertex(&quad, s->point[i + 3]);
		ml_color(&quad, s->color);
		ml_setmode(&quad, s->mode);
		ml_size(&quad, s->size);
		ml_quad_settings(&quad, s);
		ml_end(&quad);
		i += 2;
	}
}
