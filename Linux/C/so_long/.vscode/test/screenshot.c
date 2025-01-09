/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 02:23:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/17 10:30:54 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	set_pixel(t_img *img, t_img *data, t_vec2 adr)
{
	img->addr[adr.y] = data->addr[adr.x];
	img->addr[adr.y + 1] = data->addr[adr.x + 1];
	img->addr[adr.y + 2] = data->addr[adr.x + 2];
}

void	img_to_screen(t_imgx *imgx, t_imgx *box, t_vec2 ori)
{
	t_vec2	src;
	t_vec2	dest;
	t_vec2	adr;

	if (!imgx)
		return ;
	src = vec2t(0, 0);
	while (src.y < imgx->height)
	{
		src.x = 0;
		while (src.x < imgx->width)
		{
			dest = vec2t(ori.x + src.x, ori.y + src.y);
			adr.x = src.y * imgx->img.len + src.x * (imgx->img.bpp / 8);
			adr.y = dest.y * box->img.len + dest.x * (box->img.bpp / 8);
			if (imgx->img.addr[adr.x])
				set_pixel(&box->img, &imgx->img, adr);
			src.x++;
		}
		src.y++;
	}
}

void	ent_to_screen(t_core *core, t_imgx *box, t_vec2 ori, char *ent)
{
	if (*ent == g_player)
	{
		get_client(core)->origin = ori;
		*ent = g_ground;
	}
	if (*ent == g_ground)
		img_to_screen(get_img(core, "/ground.xpm"), box, ori);
}

void	map_to_screen(t_core *core, t_imgx *box, char **map)
{
	t_vec2	cs;
	t_vec2	ps;
	t_vec4	mi;

	cs = vec2t(0, 0);
	mi = get_game(core)->map_i;
	ps = vec2t(mi.x, mi.y);
	while (cs.y < get_game(core)->map_max.y && map[cs.y])
	{
		ps.x = mi.x;
		cs.x = 0;
		while (cs.x < get_game(core)->map_max.x && map[cs.y][cs.x])
		{
			ent_to_screen(core, box, ps, &map[cs.y][cs.x]);
			ps.x += 60;
			cs.x++;
		}
		ps.y += 60;
		cs.y++;
	}
	img_to_screen(get_img(core, "/l_frame_0.xpm"), box, get_client(core)->origin);
}

void	create_screenshot(t_core *core, char **map)
{
	t_mlx	*mlx;
	t_imgx	box;

	mlx = get_mlx(core);
	sl_memset(&box, 0, sizeof(t_imgx));
	box.img.ptr = mlx_new_image(mlx->ptr, get_mlx(core)->width,
			get_mlx(core)->height);
	if (!box.img.ptr)
		return ;
	box.img.addr = mlx_get_data_addr(box.img.ptr, &box.img.bpp,
			&box.img.len, &box.img.endian);
	if (!box.img.addr)
		return ;
	box.width = get_mlx(core)->width;
	box.height = get_mlx(core)->height;
	map_to_screen(core, &box, map);
	mlx_put_image_to_window(mlx->ptr, mlx->win, box.img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, box.img.ptr);
}
