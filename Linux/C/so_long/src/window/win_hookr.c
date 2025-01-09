/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_hookr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 06:37:34 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/20 06:53:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	hook_key_release(int ks, t_core *core)
{
	if (get_game(core)->stop_proc)
		return (0);
	if ((ks == get_client(core)->keybind[kb_up])
		|| (ks == XK_Up))
		core->ks.up = 0;
	if ((ks == get_client(core)->keybind[kb_down])
		|| (ks == XK_Down))
		core->ks.dw = 0;
	if ((ks == get_client(core)->keybind[kb_left])
		|| (ks == XK_Left))
		core->ks.lf = 0;
	if ((ks == get_client(core)->keybind[kb_right])
		|| (ks == XK_Right))
		core->ks.rt = 0;
	return (1);
}
