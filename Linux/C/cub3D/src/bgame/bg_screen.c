/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:29:16 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:33:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

void	bg_set_safearea(t_screen *sc)
{
	t_vec2	v;

	if (sc)
	{
		v = (t_vec2){1280 - (sc->x + 20), 720 - (sc->y + 20)};
		sc->area.a1 = (t_vec2){20 - sc->area.u.x, 20 - sc->area.u.y};
		sc->area.a2 = (t_vec2)
		{
			sc->x + v.x + sc->area.u.x,
			20 - sc->area.u.y
		};
		sc->area.a3 = (t_vec2)
		{
			sc->x + v.x + sc->area.u.x,
			sc->y + v.y + sc->area.u.y
		};
		sc->area.a4 = (t_vec2)
		{
			20 - sc->area.u.x,
			sc->y + v.y + sc->area.u.y
		};
	}
}

void	bg_register_screen(void)
{
	t_vec2	diff;
	t_ml	*lx;
	t_cb	*cub;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	if (lx && cub)
	{
		if (lx->width == 1280 && lx->height == 720)
		{
			cub->screen.x = 0;
			cub->screen.y = 0;
		}
		else
		{
			diff = (t_vec2){(lx->width - 1280), (lx->height - 720)};
			cub->screen.x = diff.x - (diff.x / 2);
			cub->screen.y = diff.y - (diff.y / 2);
		}
		cub->screen.area.u = (t_vec2){2, 80};
		bg_set_safearea(&cub->screen);
	}
}
