/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_keycode_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:03:34 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 13:37:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief get the number of key added via a ptr
/// @return ptr of count
int	*get_key_count(void)
{
	static int	n = 0;

	return (&n);
}

void	add_keycode(__uint16_t code, void (*(func))())
{
	int		i;
	t_ml	*lx;
	int		*n;

	n = get_key_count();
	i = get_key_num(code);
	lx = gmlx(ACT_GET);
	if (code > 0 && lx && *n < 256 && i == -1)
	{
		lx->key[*n].code = code;
		lx->key[*n].callback = func;
		lx->key[*n].id = *n;
		(*n)++;
		if (*n >= 256)
			xwrite(1, "key limit reached!\n", 19);
	}
	else if (code == 0)
		return ;
	else
		xwrite(1, "An Error occured in \
add_key(int code, void (*(func))())\n", 56);
}

void	init_keyboard(t_ml *lx)
{
	int	i;

	i = 0;
	if (lx)
	{
		while (i < 256)
		{
			lx->key[i].id = 0;
			lx->key[i].code = 0;
			lx->key[i].is_pressed = 0;
			lx->key[i].ignore = 0;
			lx->key[i].callback = NULL;
			i++;
		}
	}
}
