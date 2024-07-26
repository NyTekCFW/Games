/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_render_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:42:51 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/26 20:39:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

int	hook_render(t_ml *lx)
{
	if (lx && !lx->quit)
	{
		if (lx->render_callback)
			lx->render_callback(lx);
		return (0);
	}
	return (1);
}
