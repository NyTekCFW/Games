/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:08:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:17:14 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief merge 2 images at a specific position
/// @param d dest image
/// @param b base image
/// @param u position
void	merge_img(t_shaders *d, t_shaders *b, t_vec2 u)
{
	t_vec2	i;
	t_vec2	offset;

	i = (t_vec2){0, 0};
	if (d && b)
	{
		while (i.y < b->img.height)
		{
			offset = (t_vec2){((u.y + i.y) * d->img.width + u.x)
				* sizeof(__uint32_t),
				i.y * b->img.width * sizeof(__uint32_t)};
			if ((u.x >= 0) && ((u.x + b->img.width) <= d->img.width)
				&& (u.y + i.y >= 0) && (u.y + i.y < d->img.height))
				smo_copy_img(d->img.addr + offset.x, b->img.addr + offset.y,
					b->img.width * sizeof(__uint32_t));
			i.y++;
		}
	}
}

/// @brief merge 2 images at a specific position
/// basically this one is only if you use directly
// the t_img struct instead t_shaders
/// @param d dest image
/// @param b base image
/// @param u position 
void	merge_img_overlay(t_img *d, t_img *b, t_vec2 u)
{
	t_vec2	i;
	t_vec2	offset;

	i = (t_vec2){0, 0};
	if (d && b)
	{
		while (i.y < b->height)
		{
			offset = (t_vec2){((u.y + i.y) * d->width + u.x)
				* sizeof(__uint32_t),
				i.y * b->width * sizeof(__uint32_t)};
			if ((u.x >= 0) && ((u.x + b->width) <= d->width)
				&& (u.y + i.y >= 0) && (u.y + i.y < d->height))
				smo_copy_img(d->addr + offset.x, b->addr + offset.y,
					b->width * sizeof(__uint32_t));
			i.y++;
		}
	}
}
