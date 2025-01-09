/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:21:56 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/07 05:52:23 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	*win_mlx_new(t_core *core, char *title)
{
	void	*newwin;
	t_mlx	*mlx;

	mlx = get_mlx(core);
	newwin = mlx_new_window(mlx->ptr, mlx->width, mlx->height, title);
	return (newwin);
}

void	win_maker(t_core *core)
{
	if (win_config(core))
	{
		get_mlx(core)->win = win_mlx_new(core, "Minilibx Engine - So_long");
		if (!get_mlx(core)->win || !win_hook(core))
			return (win_error(core), (void)0);
	}
	exit(0);
}
