/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:34:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:06:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief insert a color at a image adr
/// @param img image
/// @param adr can be obtained by using get_px_addr(img, xy)
/// @param clr color to set at the adr
void	set_color(t_img *img, int adr, __uint32_t clr)
{
	*(__uint32_t *)(img->addr + adr) = (clr & 0x00FFFFFF);
}

/// @brief get pixel adr of img at xy position
/// @param img image
/// @param xy position
/// @return 
__uint32_t	get_px_adr(t_img *img, t_vec2 xy)
{
	int	x;
	int	y;

	if (img->width <= 0 || img->height <= 0)
		return (0);
	if (xy.x < 0)
		xy.x *= -1;
	if (xy.y < 0)
		xy.y *= -1;
	x = xy.x % img->width;
	y = xy.y % img->height;
	return (y * img->len + x * 4);
}

/// @brief get color of pixel at xy position
/// @param img image
/// @param xy position
/// @return 
__uint32_t	get_px_color(t_img *img, t_vec2 xy)
{
	__uint32_t	pick;
	__uint32_t	adr;

	adr = get_px_adr(img, xy);
	pick = *(__uint32_t *)(img->addr + adr) & 0x00FFFFFF;
	return (pick);
}

/// @brief fill a image with a specified color
/// @param dest dest image
/// @param color specified color 
void	fill_img_color(t_img *dest, __uint32_t color)
{
	__uint32_t	i;
	__uint32_t	n;
	void		*adr;

	i = 0;
	if (!dest)
		return ;
	adr = (void *)dest->addr;
	n = dest->size;
	while (i + sizeof(long) <= n)
	{
		*(__uint64_t *)(adr + i) = (__uint64_t)color << 32 | color;
		i += sizeof(long);
	}
	while (i + sizeof(int) <= n)
	{
		*(__uint32_t *)(adr + i) = (__uint32_t)color;
		i += sizeof(int);
	}
	while (i + sizeof(char) <= n)
	{
		*(__uint8_t *)(adr + i) = (__uint8_t)(color >> (i % 4) * 8);
		i += sizeof(char);
	}
}

void	fill_shader_color(char *name, __uint32_t color)
{
	t_shaders	*box;

	if (name)
	{
		box = get_img(name);
		if (box)
			fill_img_color(&box->img, color);
	}
}
