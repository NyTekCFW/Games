/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_key_num_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:39:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:17:31 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief replace the current callback function
/// @param num obtained via get_key_num(code)
/// @param func function that will
///replace the current callback
///function
void	keynum_replace(int num, void (*(func))())
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (num == -1)
	{
		xwrite(1, "Error : Key num not registered!\n", 32);
		return ;
	}
	if (lx && num >= 0 && num < 256)
		lx->key[num].callback = func;
}

/// @brief return 1 if the keynum is pressed
/// @param code num obtained via get_key_num(code)
/// @return 
int	key_pressed(int num)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && num >= 0 && num < 256)
		return (lx->key[num].is_pressed);
	return (0);
}

/// @brief check if the keynum is pressed
///and execute the func attribued if the
///func is not null
/// @param code num obtained via get_key_num(code)
/// @return 
int	keynum_execute(int num)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && num >= 0 && num < 256)
	{
		if (!lx->key[num].ignore && lx->key[num].is_pressed
			&& lx->key[num].callback != NULL)
		{
			lx->key[num].callback();
			return (1);
		}
	}
	return (0);
}

t_key	*get_key(__uint8_t id)
{
	int		n;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && id < BUTTON_MAX)
	{
		n = get_key_num(lx->config.button[id]);
		if (n >= 0 && n < 256)
			return (&lx->key[n]);
	}
	return (NULL);
}

__uint16_t	*get_buttons(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
		return (lx->config.button);
	return (NULL);
}
