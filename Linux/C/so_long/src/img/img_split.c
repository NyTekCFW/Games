/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:19:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/06 19:18:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	split_img(t_imgx **imgx, t_vec3 wh, int i)
{
	t_vec4	ifr;
	t_vec2	adr;

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
			if (get_value(imgx[0]->img.addr + adr.x) != 0xFF000000)
				set_value(imgx[1]->img.addr + adr.y,
					get_value(imgx[0]->img.addr + adr.x));
			ifr.z++;
			ifr.w = ifr.x + ifr.z;
		}
		ifr.y++;
	}
}

void	split_asset(t_core *core, t_vec3 wh, char **in)
{
	t_imgx	*imgx[2];
	int		i;
	char	tmp[50];

	imgx[0] = get_img(core, in[0]);
	insert_str(tmp, in[1], 50);
	i = 0;
	while (i < wh.z + 1)
	{
		tmp[sl_strlen(tmp) - 1] = 0x30 + i;
		imgx[1] = get_img(core, tmp);
		split_img(imgx, wh, i);
		i++;
	}
}

/*static void	split_img(t_core *core, t_vec3 wh, char *in, char *out)
{
	t_vec4	ifr;
	t_imgx	*imgx[2];
	t_vec2	adr;

	imgx[0] = get_img(core, in);
	imgx[1] = get_img(core, out);
	ifr.x = wh.z * 60;
	ifr.y = 0;
	while (ifr.y < wh.y)
	{
		ifr.z = 0;
		ifr.w = ifr.x + ifr.z;
		while (ifr.w < ifr.x + wh.x)
		{
			adr.x = ifr.y * imgx[0]->img.len + ifr.w * (imgx[0]->img.bpp / 8);
			adr.y = ifr.y * imgx[1]->img.len + ifr.z * (imgx[1]->img.bpp / 8);
			if (get_value(imgx[0]->img.addr + adr.x) != 0xFF000000)
				set_value(imgx[1]->img.addr + adr.y,
					get_value(imgx[0]->img.addr + adr.x));
			ifr.z++;
			ifr.w = ifr.x + ifr.z;
		}
		ifr.y++;
	}
}*/