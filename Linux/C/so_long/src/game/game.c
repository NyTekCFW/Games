/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 09:53:29 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/11 10:45:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	set_status(t_core *core, int status)
{
	get_game(core)->status = status;
}

int	get_status(t_core *core)
{
	return (get_game(core)->status);
}

void	set_key_status(t_core *core, int repeat)
{
	t_mlx	*mlx;

	mlx = get_mlx(core);
	if (repeat)
	{
		system("xset r rate 100 30");
		mlx_do_key_autorepeaton(mlx->ptr);
	}
	else
	{
		system("xset r rate 500 33");
		mlx_do_key_autorepeatoff(mlx->ptr);
	}
}

void	reset_key_status(t_core *core)
{
	system("xset r rate 500 33");
	mlx_do_key_autorepeaton(core->mlx.ptr);
}
