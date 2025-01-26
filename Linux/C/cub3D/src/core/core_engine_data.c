/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:55:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:35:58 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

t_shaders	*get_tex(int tex)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub && tex >= 0 && tex < TEX_MAX)
		return (cub->texture[tex]);
	return (NULL);
}

t_weapon_data	*get_wpn_data(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		return (cub->weapons);
	return (NULL);
}

t_anim	*get_wanim(int id)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub && id < 3 && id >= 0)
		return (&cub->world_anim[id]);
	return (NULL);
}
