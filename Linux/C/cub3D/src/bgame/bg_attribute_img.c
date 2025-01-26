/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_attribute_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:04:50 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:30:18 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

void	bg_attibute_xpm(void)
{
	t_shaders	**textures;
	t_map		*_map;

	textures = get_textures();
	_map = get_map();
	if (textures && _map)
	{
		textures[TEX_WALL_SOUTH] = get_img("/brick_red.xpm");
		textures[TEX_WALL_NORTH] = get_img("/brick_white.xpm");
		textures[TEX_WALL_EAST] = get_img("/cinderblock.xpm");
		textures[TEX_WALL_WEST] = get_img("/roof_brick.xpm");
		textures[TEX_RENDER] = get_img("framework");
		textures[TEX_DOOR_CLOSE] = get_img("/door_closed.xpm");
	}
}
