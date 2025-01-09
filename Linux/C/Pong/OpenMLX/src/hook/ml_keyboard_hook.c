/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_keyboard_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:36:57 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:16:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief release button handler
/// @param ks button released
/// @param data null or what u want
/// @return true
int	hook_keyboard_r(int ks, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		if (ks > 0xFFFF)
			return (0);
		set_keycode_status(ks, 0);
	}
	return (1);
}

/// @brief press button handler
/// @param ks button pressed
/// @param data null or what u want
/// @return true
int	hook_keyboard_p(int ks, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		if (ks > 0xFFFF)
			return (0);
		set_keycode_status(ks, 1);
	}
	return (1);
}
