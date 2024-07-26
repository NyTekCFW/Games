/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:14:13 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:17:10 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief update the buffer name id
///e.g : monospace_ttf_000 -> monospace_ttf_001
/// @param buffer e.g: monospace_ttf_
/// @param len len of the buffer
/// @param i current id
static void	update_splitted_name(char *buffer, size_t len, int i)
{
	buffer[len] = 0x30 + (i / 100);
	buffer[len + 1] = 0x30 + ((i / 10) % 10);
	buffer[len + 2] = 0x30 + (i % 10);
	buffer[len + 3] = 0;
}

/// @brief split the image
/// @param imgx image array [2] that contain
///the image source and destination
/// @param wh wh.x = position where
///the image will be splitted and .y = height of the image
/// @param i current id
static void	split(t_shaders **imgx, t_vec2 wh, int i)
{
	t_vec4		ifr;
	t_vec2		adr;
	__uint32_t	v;

	ifr.x = i * wh.x;
	ifr.y = 0;
	while (ifr.y < wh.y)
	{
		ifr.z = 0;
		ifr.w = ifr.x + ifr.z;
		while (ifr.w < ifr.x + wh.x)
		{
			adr.x = ifr.y * imgx[0]->img.len + ifr.w * (imgx[0]->img.bpp / 8);
			adr.y = ifr.y * imgx[1]->img.len + ifr.z * (imgx[1]->img.bpp / 8);
			set_value(imgx[1]->img.addr + adr.y, 0);
			v = get_value(imgx[0]->img.addr + adr.x);
			if (v != 0xFF000000)
				set_value(imgx[1]->img.addr + adr.y, v);
			ifr.z++;
			ifr.w = ifr.x + ifr.z;
		}
		ifr.y++;
	}
}

/// @brief 
/// @param name name of the shaders e.g :
/// /monospace_ttf.xpm
/// @param output base name of output splitted image
/// e.g: mm_ -> mm_000 -> mm_001 ...
/// @param width width of 1 image
/// @param i continue a list of splitted image
/// e.g: int a = split_image("/p1.xpm", "b", 2, 0);
/// a = split_image("/p2.xpm", "b", 2, a);
/// @return total of image splitted (last id)
int	split_image(char *name, char *output, int width, int i)
{
	t_shaders	*imgx[2];
	char		*buffer;
	int			u;

	u = 0;
	if (xalloc((void **)&buffer, sizeof(char), xstrlen(output) + 5))
	{
		imgx[0] = get_img(name);
		xmemcpy(buffer, output, xstrlen(output));
		if (imgx[0])
		{
			while (u < (imgx[0]->img.width / width))
			{
				update_splitted_name(buffer, xstrlen(output), i + u);
				create_img((t_ui){width, imgx[0]->img.height, 0},
					NULL, buffer);
				imgx[1] = get_img(buffer);
				if (imgx[1])
					split(imgx, (t_vec2){width, imgx[0]->img.height}, u);
				u++;
			}
		}
		xfree((void **)&buffer);
	}
	return (i + u);
}
