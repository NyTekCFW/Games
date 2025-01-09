/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:25 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/21 07:19:04 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	add_img_info(t_core *core, t_imgx *imgx, char *path)
{
	imgx->img.ptr = mlx_xpm_file_to_image(get_mlx(core)->ptr,
			path, &imgx->width, &imgx->height);
	imgx->img.addr = mlx_get_data_addr(imgx->img.ptr,
			&imgx->img.bpp, &imgx->img.len, &imgx->img.endian);
	imgx->file = sl_hashstr(sl_strrchr(path, '/'));
	imgx->next = NULL;
}

static void	add_imgx(t_core *core, t_imgx *new)
{
	t_imgx	*imgx;

	imgx = &core->shaders;
	while (imgx && imgx->next)
		imgx = imgx->next;
	imgx->next = malloc(sizeof(t_imgx));
	sl_memset(imgx->next, 0, sizeof(t_imgx));
	sl_memcpy(imgx->next, new, sizeof(t_imgx));
}

void	create_img(t_core *core, t_ui ui, void (*func)(), char *name)
{
	t_mlx	*mlx;
	t_imgx	box;

	mlx = get_mlx(core);
	sl_memset(&box, 0, sizeof(t_imgx));
	box.file = sl_hashstr(name);
	box.height = ui.h;
	box.width = ui.w;
	box.next = NULL;
	box.img.ptr = mlx_new_image(mlx->ptr, ui.w, ui.h);
	if (!box.img.ptr)
		return ;
	box.img.addr = mlx_get_data_addr(box.img.ptr,
			&box.img.bpp, &box.img.len, &box.img.endian);
	if (!box.img.addr)
		return ;
	if (func)
		func(&box.img, ui);
	add_imgx(core, &box);
}

void	add_img(t_core *core, char *path)
{
	t_imgx	*imgx;

	imgx = &core->shaders;
	if (!core->shaders.file)
	{
		add_img_info(core, &core->shaders, path);
		return ;
	}
	while (imgx && imgx->next)
		imgx = imgx->next;
	imgx->next = malloc(sizeof(t_imgx));
	sl_memset(imgx->next, 0, sizeof(t_imgx));
	add_img_info(core, imgx->next, path);
}
