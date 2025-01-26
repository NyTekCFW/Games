/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:24:21 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/27 00:46:07 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../openmlx/includes/openmlx.h"

typedef struct cb_s
{
	t_screen		screen;
	t_map			map_data;
	t_player		player;
	t_vars			var;
	t_weapon_data	weapons[2];
	t_shaders		*texture[6];
	t_anim			world_anim[3];
	int				stop_handler;
}	t_cb;

//cub struct
t_cb		*g_cub(int act);
void		g_exit(void);
#endif
