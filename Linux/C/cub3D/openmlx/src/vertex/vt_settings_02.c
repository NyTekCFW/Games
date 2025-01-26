/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_settings_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:38:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:43:24 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief fix overwrite of the shader
///set for the render of the
/// current primitive
/// @param s current primitive
/// @param ijt position data
void	ml_overwrite_fix(t_prim *s, t_vec4 *ijt)
{
	if (ijt->w >= s->savemesh->height)
		ijt->w = s->savemesh->height - 1;
	else if (ijt->w < 0)
		ijt->w = 0;
	if (ijt->y >= s->savemesh->width)
		ijt->y = s->savemesh->width - 1;
	else if (ijt->y < 0)
		ijt->y = 0;
}

/// @brief set if you want to use
///the overflow fix function
/// @param s current primitive
/// @param overwrite 1 = Use fix
void	ml_overwrite(t_prim *s, int overwrite)
{
	if (overwrite >= 0 && overwrite < 2)
		s->overwrite = overwrite;
}

static void	register_mesh_img(t_vec2 max, t_vec2 min, t_prim *s, char *name)
{
	t_shaders	*sh;
	t_vec2		wh;

	if (max.x < 0)
		max.x *= -1;
	if (min.x < 0)
		min.x *= -1;
	wh.x = max.x - min.x;
	if (max.y < 0)
		max.y *= -1;
	if (min.y < 0)
		min.y *= -1;
	wh.y = max.y - min.y;
	if (wh.x > 1 && wh.y > 1)
	{
		if (get_img(name) == NULL)
			create_img((t_ui){wh.x, wh.y, 0}, fill_img_color, name);
		sh = get_img(name);
		if (sh)
		{
			ml_savemesh(s, name);
			ml_overwrite(s, s->overwrite);
			ml_end(s);
		}
	}
}

/// @brief replace ml_end function,
///export all data to build a 
///internal image with primitive
///settings
/// @param s current primitive
/// @param name output mesh image name
void	create_img_mesh(t_prim *s, char *name)
{
	int			i;
	t_vec2		min;
	t_vec2		max;

	i = 0;
	if (s->cpoint > 0)
	{
		min = s->point[0];
		max = s->point[0];
		while (i < s->cpoint)
		{
			if (s->point[i].x < min.x)
				min.x = s->point[i].x;
			else if (s->point[i].x > max.x)
				max.x = s->point[i].x;
			if (s->point[i].y < min.y)
				min.y = s->point[i].y;
			else if (s->point[i].y > max.y)
				max.y = s->point[i].y;
			i++;
		}
		register_mesh_img(max, min, s, name);
	}
}
