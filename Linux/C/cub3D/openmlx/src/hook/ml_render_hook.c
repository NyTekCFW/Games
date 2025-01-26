/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_render_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:42:51 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 19:01:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

int	hook_render(t_ml *lx)
{
	int		i;

	i = -1;
	if (lx && !lx->quit)
	{
		if (lx->render_callback)
			lx->render_callback(lx);
		while (++i < *get_key_count())
			keynum_execute(i);
		return (0);
	}
	return (1);
}
