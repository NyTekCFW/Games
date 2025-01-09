/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:41:59 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/20 08:30:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	auto_map_center(t_core *core, t_vec2 *mpx, t_vec2 *cen)
{
	if (mpx->x * 60 >= get_mlx(core)->width)
	{
		get_game(core)->map_i.x = 0;
		get_game(core)->map_i.z = get_mlx(core)->width;
	}
	else
	{
		get_game(core)->map_i.x = cen->x - ((mpx->x * 60) / 2);
		get_game(core)->map_i.z = (cen->x - (mpx->x / 2)) + (mpx->x * 60);
	}
	if (mpx->y * 60 >= get_mlx(core)->height)
	{
		get_game(core)->map_i.y = 0;
		get_game(core)->map_i.w = get_mlx(core)->height;
	}
	else
	{
		get_game(core)->map_i.y = cen->y - ((mpx->y * 60) / 2);
		get_game(core)->map_i.w = (cen->y - (mpx->y / 2)) + (mpx->y * 60);
	}
}

static void	get_zone_count(t_core *core)
{
	float	i;
	float	u;

	i = (get_game(core)->map_max.x * 60) / get_mlx(core)->width;
	u = (get_game(core)->map_max.y * 60) / get_mlx(core)->height;
	get_game(core)->map_zone = vec2t((int)i, (int)u);
}

static void	init_cam(t_core *core, char *ent, t_vec2 ori)
{
	int		x;
	float	i;
	float	u;

	x = 0;
	if (*ent == g_player)
	{
		i = (ori.x * 60) / get_mlx(core)->width;
		u = (ori.y * 60) / get_mlx(core)->height;
		get_client(core)->zones = vec2t((int)i, (int)u);
		while (x < get_client(core)->zones.x)
		{
			get_game(core)->map_rng.x += get_mlx(core)->width / 60;
			x++;
		}
		x = 0;
		while (x < get_client(core)->zones.y)
		{
			get_game(core)->map_rng.y += get_mlx(core)->height / 60;
			x++;
		}
	}
}

void	set_map_origin(t_core *core)
{
	t_vec2	cen;

	cen = vec2t(get_mlx(core)->width / 2, get_mlx(core)->height / 2);
	auto_map_center(core, &get_game(core)->map_max, &cen);
	get_zone_count(core);
	browse_map(core, init_cam);
}
