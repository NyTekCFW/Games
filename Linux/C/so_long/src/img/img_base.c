/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 07:45:50 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/01 09:50:11 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_img(t_core *core)
{
	add_local_img(core);
	add_ui_img(core);
	add_wall_img(core);
	add_img_anim(core);
}

void	print_img(t_core *core, t_vec2 pos, char *name)
{
	t_mlx	*mlx;
	t_imgx	*imgx;

	mlx = get_mlx(core);
	imgx = &core->shaders;
	while (imgx && imgx->file != sl_hashstr(name))
		imgx = imgx->next;
	if (!imgx)
		return ;
	mlx_put_image_to_window(mlx->ptr, mlx->win, imgx->img.ptr, pos.x, pos.y);
}

void	purge_img(t_core *core)
{
	t_imgx	*prev;
	t_imgx	*list;

	list = &core->shaders;
	while (list)
	{
		while (list->next)
		{
			prev = list;
			list = list->next;
		}
		mlx_destroy_image(get_mlx(core)->ptr, list->img.ptr);
		if (prev->next)
		{
			free(prev->next);
			prev->next = NULL;
			list = &core->shaders;
		}
		else
			break ;
	}
}

t_imgx	*get_img(t_core *core, char *name)
{
	t_imgx	*imgx;

	imgx = &core->shaders;
	while (imgx && imgx->file != sl_hashstr(name))
		imgx = imgx->next;
	if (!imgx)
		return (NULL);
	return (imgx);
}
