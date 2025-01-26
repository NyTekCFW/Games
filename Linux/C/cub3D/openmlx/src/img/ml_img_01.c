/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:11:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/23 21:59:27 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief check if the current color is correct
/// @param c color
/// @return 
int	is_valid_color(__uint32_t c)
{
	return ((c != 0 && c != 0xFF000000));
}

/// @brief check if background and foreground color is valid
/// @param bkg color of the current pixel of the background
/// @param frg color of the current pixel of the foreground
/// @return 
static int	is_valid_blender(__uint32_t bkg, __uint32_t frg)
{
	if (frg == 0 || frg == 0xFF000000)
		return (0);
	else if (bkg == 0 || bkg == 0xFF000000)
	{
		if (is_valid_color(frg))
			return (1);
		else
			return (0);
	}
	return (1);
}

/// @brief 
/// @param bkg color of the current pixel of the background
/// @param frg color of the current pixel of the foreground
/// @param alpha alpha of the foreground image
/// @return 
__uint32_t	blend_colors(__uint32_t bkg, __uint32_t frg, float alpha)
{
	t_vec3		color_bkg;
	t_vec3		color_frg;
	t_vec3		color_res;
	__uint32_t	res;

	if (alpha < 0.0f)
		alpha = 0.0f;
	else if (alpha > 1.0f)
		alpha = 1.0f;
	if (!is_valid_blender(bkg, frg))
		return (0);
	color_bkg = (t_vec3){(bkg & 0xFF), (bkg >> 8) & 0xFF, (bkg >> 16) & 0xFF};
	color_frg = (t_vec3){(frg & 0xFF), (frg >> 8) & 0xFF, (frg >> 16) & 0xFF};
	color_res.x = alpha * color_frg.x + (1.0f - alpha) * color_bkg.x;
	color_res.y = alpha * color_frg.y + (1.0f - alpha) * color_bkg.y;
	color_res.z = alpha * color_frg.z + (1.0f - alpha) * color_bkg.z;
	res = ((__uint32_t)color_res.z << 16) | ((__uint32_t)color_res.y << 8)
		| ((__uint32_t)color_res.x);
	return (res);
}

/// @brief make a overlay between 2 image
///of the same size and export it on a other
/// @param d dest image the result will be stock on it
/// @param b background image
/// @param f foreground image
/// @param a alpha of the foreground
void	overlay_images(t_img *d, t_img *b, t_img *f, float a)
{
	__uint32_t	i;
	__uint32_t	color;

	i = 0;
	if (!d || !b || !f)
		return ;
	if (d->width != b->width || d->width != f->width
		|| d->height != b->height || d->height != f->height)
		return ;
	merge_img_overlay(d, b, (t_vec2){0, 0});
	while (i < d->size)
	{
		color = blend_colors(get_value(b->addr + i),
				get_value(f->addr + i), a);
		if (is_valid_color(color))
			set_value(d->addr + i, color);
		i += 4;
	}
}
