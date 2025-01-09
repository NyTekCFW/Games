/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 02:39:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/20 23:45:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_vec3	argb_to_rgb(__uint32_t clr)
{
	return (vec3t(clr & 0xFF, (clr >> 8) & 0xFF, (clr >> 16) & 0xFF));
}

void	set_color(t_img *img, int adr, __uint32_t clr)
{
	t_vec3	rgb;

	rgb = argb_to_rgb(clr);
	img->addr[adr] = rgb.x;
	img->addr[adr + 1] = rgb.y;
	img->addr[adr + 2] = rgb.z;
}

__uint32_t	get_px_color(t_img *img, int adr)
{
	__uint32_t	pick;

	pick = img->addr[adr + 2] << 16;
	pick += img->addr[adr + 1] << 8;
	pick += img->addr[adr];
	return (pick);
}

__uint32_t	get_px_adr(t_img *img, t_vec2 xy)
{
	return (xy.y * img->len + xy.x * (img->bpp / 8));
}
