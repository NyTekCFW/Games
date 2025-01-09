/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_keycode_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:58:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:17:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief get the keycode number in list
/// @param code e.g: XK_w, XK_a ....
/// @return -1 = not found -2 error
/// else is the num of the keycode
int	get_key_num(__uint16_t code)
{
	int		i;
	int		*n;
	t_ml	*lx;

	i = -1;
	lx = gmlx(ACT_GET);
	if (lx)
	{
		if (code > 0)
		{
			n = get_key_count();
			while (++i < *n)
			{
				if (lx->key[i].code == code)
					return (i);
			}
		}
		else
			xwrite(1, "Error : invalid keycode\n", 24);
		return (-1);
	}
	xwrite(1, "Error : gmlx is null\n", 19);
	return (-2);
}

/// @brief replace the current callback function
/// @param code e.g: XK_w, XK_a ....
/// @param func function that will
///replace the current callback
///function
void	keycode_replace(__uint16_t code, void (*(func))())
{
	int		i;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (i == -1)
	{
		xwrite(1, "Error : Key code not registered!\n", 33);
		return ;
	}
	if (lx && i >= 0 && i < 256)
		lx->key[i].callback = func;
}

/// @brief Call this function to set
/// if the keycode is pressed or not
/// @param code e.g: XK_w, XK_a ....
/// @param active 1 = true 0 = false 
void	set_keycode_status(__uint16_t code, __uint8_t active)
{
	int		i;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (lx && i >= 0 && i < 256)
	{
		if (!lx->key[i].ignore || (lx->key[i].ignore && !active))
			lx->key[i].is_pressed = active;
		if (!active)
			lx->key[i].ignore = 0;
	}
}

/// @brief return 1 if the keycode is pressed
/// @param code e.g: XK_w, XK_a ....
/// @return 
int	keycode_pressed(__uint16_t code)
{
	t_ml	*lx;
	int		i;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (lx && i >= 0 && i < 256)
		return (lx->key[i].is_pressed);
	return (0);
}
