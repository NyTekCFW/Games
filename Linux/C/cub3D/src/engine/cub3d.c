/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:34:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:13 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	_g_exit(void)
{
	int	i;
	int	n;
	int	*p;

	i = -1;
	p = get_key_count();
	n = *p;
	*p = 0;
	while (++i < n)
		keynum_replace(i, NULL);
}

t_cb	*g_cub(int act)
{
	static t_cb	*cub;

	if (act == ACT_INIT && xalloc((void **)&cub, 1, sizeof(t_cb)))
	{
		bg_register_screen();
		bg_register_weapondata();
		g_registerdvars();
		bg_map_register();
		bg_registerclient();
		bg_register_world_anim();
		return (cub);
	}
	else if (act == ACT_GET && cub)
		return (cub);
	else if (act == ACT_FREE && cub)
		return (xfree((void **)&cub), NULL);
	return (NULL);
}

void	g_exit(void)
{
	t_ml	*lx;
	t_cb	*cub;
	int		i;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	if (cub && lx && !cub->stop_handler)
	{
		cub->stop_handler = 1;
		mlx_mouse_show(lx->ptr, lx->win);
		mlx_loop_end(lx->ptr);
		xfree((void **)&cub->player.weapon);
		i = 0;
		while (i < cub->map_data.height)
		{
			xfree((void **)&cub->map_data.map[i]);
			++i;
		}
		xfree((void **)&cub->map_data.map);
		_g_exit();
	}
}
