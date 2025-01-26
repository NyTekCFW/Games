/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 23:06:28 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/engine/common.h"
#include "../includes/weapons/sp_weapons.h"
#include "../includes/game/g_client_move.h"
#include "../includes/game/g_client_script.h"
#include "../includes/game/g_sound.h"
#include "../includes/core/parsing.h"
#include "../includes/bgame/bg_register_trigger.h"
#include "../includes/game/g_axis.h"

int	main(int ac, char **av)
{
	t_ml	*lx;
	t_cb	*cub;

	if (check_entry(ac, av))
	{
		lx = gmlx(ACT_INIT);
		if (lx)
		{
			lx->purge_color = 0x030303;
			if (lx->make_window("Ray of the Dead", (t_vec2){1280, 720}, 0))
			{
				cub = g_cub(ACT_INIT);
				init_imgui();
				if (cub)
				{
					display_map_loading(av[1], &cub->screen, lx);
					dbg_menu(ACT_FREE);
					get_trigger(ACT_FREE);
					g_cub(ACT_FREE);
				}
				lx->quit_window();
			}
		}
	}
}
