/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_mouse_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:42:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/18 14:45:26 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief mouse button pressed handler
/// @param ks mouse button code
/// @param x x position in window
/// @param y y position in window
/// @param data ptr to handle
int	hook_mouse_p(int ks, int x, int y, t_ml *lx)
{
	if (ks > 0xFFFF)
		return (0);
	if (lx && !lx->quit)
	{
		set_keycode_status(ks, 1);
		if (ks == XK_MOUSE_SCROLL_DOWN
			|| ks == XK_MOUSE_SCROLL_UP)
			keynum_execute(get_key_num(ks));
		if (lx->mouse_p_callback)
			lx->mouse_p_callback(ks, x, y, lx);
	}
	return (1);
}

/// @brief mouse button release handler
/// @param ks mouse button code
/// @param x x position in window
/// @param y y position in window
/// @param data ptr to handle
int	hook_mouse_r(int ks, int x, int y, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		(void)x;
		(void)y;
		if (ks > 0xFFFF)
			return (0);
		set_keycode_status(ks, 0);
	}
	return (1);
}

/// @brief mouse motion handler
/// @param x x position in window
/// @param y y position in window
/// @param data ptr to handle
int	hook_mouse_m(int x, int y, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		if (lx->mouse_m_callback)
			lx->mouse_m_callback(x, y);
	}
	return (1);
}
