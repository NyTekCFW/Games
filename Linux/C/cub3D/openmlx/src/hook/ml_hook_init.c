/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_hook_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:39:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/23 21:31:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

int	end_hook(t_ml *lx)
{
	if (lx && lx->end_hook_callback)
		lx->end_hook_callback();
	return (1);
}

void	start_hook(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard_p, lx);
		mlx_hook(lx->win, KeyRelease, (1L << 1), hook_keyboard_r, lx);
		mlx_hook(lx->win, MotionNotify, (1L << 6), hook_mouse_m, lx);
		mlx_hook(lx->win, ButtonPress, (1L << 2), hook_mouse_p, lx);
		mlx_hook(lx->win, ButtonRelease, (1L << 3), hook_mouse_r, lx);
		mlx_hook(lx->win, 17, 0L, end_hook, lx);
		mlx_loop_hook(lx->ptr, hook_render, lx);
		mlx_loop(lx->ptr);
	}
}
