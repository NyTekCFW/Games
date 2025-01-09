/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:18:15 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/17 07:49:03 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_vec3	p_new_zone_x(t_mlx *mlx, t_game *gm, t_client *cl)
{
	t_vec3	data;

	data = vec3t(cl->origin.x, cl->zones.x, gm->map_rng.x);
	if (gm->map_zone.x > 0 && cl->origin.x >= mlx->width - 40
		&& cl->zones.x + 1 <= gm->map_zone.x
		&& cl->dir == kb_right)
	{
		cl->origin.x = 5;
		cl->zones.x++;
		gm->map_rng.x += mlx->width / 60;
		cl->new_zone = 1;
	}
	else if (gm->map_zone.x > 0 && cl->origin.x <= -1
		&& cl->zones.x - 1 > -1
		&& cl->dir == kb_left)
	{
		cl->origin.x = mlx->width - 44;
		cl->zones.x--;
		gm->map_rng.x -= mlx->width / 60;
		cl->new_zone = 1;
	}
	return (data);
}

static t_vec3	p_new_zone_y(t_mlx *mlx, t_game *gm, t_client *cl)
{
	t_vec3	data;

	data = vec3t(cl->origin.y, cl->zones.y, gm->map_rng.y);
	if (gm->map_zone.y > 0 && cl->origin.y >= mlx->height - 40
		&& cl->zones.y + 1 <= gm->map_zone.y
		&& cl->dir == kb_down)
	{
		cl->origin.y = 5;
		cl->zones.y++;
		gm->map_rng.y += mlx->height / 60;
		cl->new_zone = 1;
	}
	else if (gm->map_zone.y > 0 && cl->origin.y <= -1
		&& cl->zones.y - 1 > -1
		&& cl->dir == kb_up)
	{
		cl->origin.y = mlx->height - 44;
		cl->zones.y--;
		gm->map_rng.y -= mlx->height / 60;
		cl->new_zone = 1;
	}
	return (data);
}

static void	zone_check(t_core *core)
{
	t_mlx		*mlx;
	t_game		*gm;
	t_client	*cl;
	t_vec3		data;

	mlx = get_mlx(core);
	cl = get_client(core);
	gm = get_game(core);
	data = p_new_zone_x(mlx, gm, cl);
	if (p_check_zone(core, data, 0))
	{
		data = p_new_zone_y(mlx, gm, cl);
		if (p_check_zone(core, data, 1) && get_client(core)->new_zone)
			mlx_clear_window(mlx->ptr, mlx->win);
	}
	get_client(core)->new_zone = 0;
}

void	p_move(t_core *core, int *val, int spm, int dir)
{
	if (get_status(core) != status_main)
	{
		get_client(core)->old_origin = get_client(core)->origin;
		*val += spm;
		if (dir != get_client(core)->dir)
		{
			if (dir == kb_up)
				change_pview(core, 'b');
			if (dir == kb_down)
				change_pview(core, 'f');
			if (dir == kb_left)
				change_pview(core, 'l');
			if (dir == kb_right)
				change_pview(core, 'r');
			get_client(core)->dir = dir;
		}
		browse_map(core, p_can_move);
		zone_check(core);
		if (t_vec2cmp(get_client(core)->origin, get_client(core)->old_origin))
			add_steps(core);
	}
}
