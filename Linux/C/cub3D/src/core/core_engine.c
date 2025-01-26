/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:53:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

t_player	*get_user(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		return (&cub->player);
	return (NULL);
}

t_screen	*get_screen(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		return (&cub->screen);
	return (NULL);
}

t_vars	*get_var(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		return (&cub->var);
	return (NULL);
}

t_map	*get_map(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		return (&cub->map_data);
	return (NULL);
}

t_shaders	**get_textures(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		return (cub->texture);
	return (NULL);
}
