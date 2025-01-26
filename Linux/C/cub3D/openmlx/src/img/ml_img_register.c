/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 06:21:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/26 03:44:40 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief get and return the image size
/// @param sh image that you want to know the size
/// @return 
static __uint32_t	get_img_size(t_shaders *sh)
{
	if (sh)
		return (sh->img.height * sh->img.len
			+ sh->img.width * (sh->img.bpp / 8));
	return (0);
}

/// @brief store shader with his info into a list
/// @param new 
static void	store_shaders(t_shaders *new)
{
	t_ml		*lx;
	t_shaders	*sh;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		sh = &lx->texture.shaders;
		if (!sh->is_stored)
		{
			xmemcpy(sh, new, sizeof(t_shaders));
			sh->is_stored = 1;
		}
		else
		{
			while (sh && sh->next)
				sh = sh->next;
			if (xalloc((void **)&sh->next, sizeof(t_shaders), 1))
			{
				xmemcpy(sh->next, new, sizeof(t_shaders));
				sh->next->is_stored = 1;
			}
		}
		lx->texture.shaders_count += 1;
	}
}

/// @brief make your own image with dimension, a specified color,
///and the possibility to use all gived info by ui
///to call a function after the image is created
/// @param ui t_ui struct
/// @param func function that u want call (func(t_img *, t_ui))
/// @param name the name of the image
void	create_img(t_ui ui, void (*func)(), char *name)
{
	t_ml		*lx;
	t_shaders	box;

	lx = gmlx(ACT_GET);
	if (lx && get_img(name) == NULL)
	{
		xmemset(&box, 0, sizeof(t_shaders));
		box.file = fnv1a_hash(name);
		xstrcpy(box.img_name, name);
		box.img.height = ui.h;
		box.img.width = ui.w;
		box.next = NULL;
		box.img.ptr = mlx_new_image(lx->ptr, ui.w, ui.h);
		if (!box.img.ptr)
			return ;
		box.img.addr = mlx_get_data_addr(box.img.ptr,
				&box.img.bpp, &box.img.len, &box.img.endian);
		box.img.size = get_img_size(&box);
		if (func == fill_img_color)
			func(&box.img, ui.color);
		else if (func)
			func(&box.img, ui);
		store_shaders(&box);
	}
}

/// @brief register an local image .xpm e.g:
///"./texture/ground.xpm" -> image name will be /ground.xpm
/// @param path path of the image .xpm
void	register_img(char *path)
{
	t_ml		*lx;
	t_shaders	sh;
	int			fd;
	char		*ab;

	lx = gmlx(ACT_GET);
	sh = (t_shaders){0};
	if (lx && path && path[0])
	{
		fd = open(path, O_RDONLY);
		ab = xstrrchr(path, '/');
		if (fd > 0 && lx && !get_img(ab))
		{
			close(fd);
			sh.img.ptr = mlx_xpm_file_to_image(lx->ptr,
					path, &sh.img.width, &sh.img.height);
			sh.img.addr = mlx_get_data_addr(sh.img.ptr,
					&sh.img.bpp, &sh.img.len, &sh.img.endian);
			sh.file = fnv1a_hash(ab);
			xstrcpy(sh.img_name, ab);
			sh.next = NULL;
			sh.img.size = get_img_size(&sh);
			store_shaders(&sh);
		}
	}
}
