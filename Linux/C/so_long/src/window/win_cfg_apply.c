/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_cfg_apply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:39:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/11 08:14:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	apply_reso(t_core *core, int width, int height, int id)
{
	if ((get_mlx(core)->width * get_mlx(core)->height) >= (width * height))
	{
		get_mlx(core)->width = width;
		get_mlx(core)->height = height;
		get_account(core)->reso = id;
	}
	else
		get_account(core)->reso = r_2160p;
}

void	apply_keybinds(t_core *core)
{
	if (k_qwerty == get_account(core)->keyboard)
	{
		get_client(core)->keybind[kb_up] = XK_w;
		get_client(core)->keybind[kb_left] = XK_a;
	}
	else if (k_azerty == get_account(core)->keyboard)
	{
		get_client(core)->keybind[kb_up] = XK_z;
		get_client(core)->keybind[kb_left] = XK_q;
	}
	get_client(core)->keybind[kb_down] = XK_s;
	get_client(core)->keybind[kb_right] = XK_d;
}
