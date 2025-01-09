/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:34:51 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/28 03:21:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	free_map(t_core *core, t_vec2 xy)
{
	int	i;

	i = 0;
	if (core->game.map)
	{
		while (i < xy.y && core->game.map[i])
		{
			if (core->game.map[i])
			{
				free(core->game.map[i]);
				core->game.map[i] = NULL;
			}
			i++;
		}
		free(core->game.map);
		core->game.map = NULL;
	}
}

int	win_error(t_core *core)
{
	t_vec2	xy;
	t_game	*gm;

	gm = get_game(core);
	gm->stop_proc = 1;
	xy = gm->map_max;
	gm->map_max = vec2t(0, 0);
	if (get_mlx(core)->ptr)
	{
		mlx_destroy_display(get_mlx(core)->ptr);
		free(get_mlx(core)->ptr);
		get_mlx(core)->ptr = NULL;
	}
	free_map(core, xy);
	playsound("leave_game", 0, 1, 0);
	exit(1);
	return (0);
}

int	win_exit(t_core *core)
{
	t_vec2	xy;
	t_game	*gm;

	gm = get_game(core);
	gm->stop_proc = 1;
	xy = gm->map_max;
	gm->map_max = vec2t(0, 0);
	playsound("leave_game", 0, 1, 0);
	free_map(core, xy);
	make_save(core);
	purge_img(core);
	info_free(core);
	leaderboard_free(core);
	clear_all_cmd(core);
	mlx_loop_end(get_mlx(core)->ptr);
	system("xset r rate 500 33");
	return (1);
}
