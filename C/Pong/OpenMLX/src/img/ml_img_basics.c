/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:25:08 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/23 22:07:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief destroy a shader struct
/// @param lx obtained via gmlx
/// @param prev previous shader on the list
/// @param list list that contain all shaders
/// @return 
static int	purge_shader(t_ml *lx, t_shaders *prev, t_shaders *list)
{
	if (lx)
	{
		if (list->img.ptr)
			mlx_destroy_image(lx->ptr, list->img.ptr);
		if (lx->texture.shaders_count > 0)
			lx->texture.shaders_count -= 1;
		if (prev && prev->next)
		{
			xfree((void **)&prev->next);
			return (1);
		}
	}
	return (0);
}

/// @brief purges all shaders registered
/// @param  
void	purge_textures(void)
{
	t_ml		*lx;
	t_shaders	*prev;
	t_shaders	*list;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		list = &lx->texture.shaders;
		prev = list;
		while (list)
		{
			while (list->next)
			{
				prev = list;
				list = list->next;
			}
			if (!purge_shader(lx, prev, list))
				break ;
			else
				list = &lx->texture.shaders;
		}
	}
}

/// @brief print a image into the window
/// @param pos position
/// @param name name of the shader
void	print_img(t_vec2 pos, char *name)
{
	t_ml		*lx;
	t_shaders	*sh;

	lx = gmlx(ACT_GET);
	if (lx && name && name[0])
	{
		sh = &lx->texture.shaders;
		while (sh && sh->file != fnv1a_hash(name))
			sh = sh->next;
		if (!sh)
			return ;
		if (lx->ptr && lx->win && sh->img.ptr)
			mlx_put_image_to_window(lx->ptr, lx->win,
				sh->img.ptr, pos.x, pos.y);
	}
}

/// @brief return a shader struct obtained via a name
/// @param name name of the shader
/// @return 
t_shaders	*get_img(char *name)
{
	t_ml		*lx;
	t_shaders	*sh;

	lx = gmlx(ACT_GET);
	if (lx && name && name[0])
	{
		sh = &lx->texture.shaders;
		while (sh && sh->file != fnv1a_hash(name))
			sh = sh->next;
		if (!sh)
			return (NULL);
		return (sh);
	}
	return (NULL);
}
