/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:43:35 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 03:01:03 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

#ifndef SO_LONG_PROJECT

/// @brief insert a pixel into the window
/// @param x position x of the window
/// @param y position y of the window
/// @param color color
void	ml_put_pixel(int x, int y, __uint32_t color)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && lx->ptr && lx->win)
	{
		if (x >= 0 && x <= lx->width
			&& y >= 0 && y <= lx->height)
			mlx_pixel_put(lx->ptr, lx->win, x, y, color);
	}
}
#else

/// @brief mlx_pixel_put rebuilded with pixel image
/// @param x position x of the window
/// @param y position y of the window
/// @param color color to set before print the image
void	ml_put_pixel(int x, int y, __uint32_t color)
{
	t_ml		*lx;
	t_shaders	*sh;
	static int	r;
	char		buffer[13];

	lx = gmlx(ACT_GET);
	if (r < 0 || r > 254)
		r = 0;
	xstrcpy(buffer, "ui_pixel_000");
	buffer[9] = 0x30 + (r / 100);
	buffer[10] = 0x30 + ((r / 10) % 10);
	buffer[11] = 0x30 + (r % 10);
	sh = get_img(buffer);
	if (lx && lx->ptr && lx->win && sh)
	{
		fill_img_color(&sh->img, color);
		if (x >= 0 && x <= lx->width
			&& y >= 0 && y <= lx->height)
			print_img((t_vec2){x, y}, buffer);
		r++;
	}
}
#endif