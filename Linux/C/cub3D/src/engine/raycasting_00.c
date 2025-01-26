/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:03:57 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:18 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	ray_fix_line(t_ray *ray, int a)
{
	char	c;

	c = ray->entity;
	if (ent_is_perks(c) || (ent_is_trap(c) && a))
	{
		if (c == 'D' && a > 0)
			ray->line_height = (int)(355 / ray->pwall_dist);
		else
			ray->line_height = (int)(360 / ray->pwall_dist);
		ray->draw_start = ray->draw_end - ray->line_height;
		ray->draw_end = ray->draw_end;
	}
}

void	ray_line(t_ray *ray, void *cub, int a)
{
	t_cb	*cb;

	cb = (t_cb *)cub;
	if (!ray->entity)
		ray->entity = '1';
	if (ray->side == 0)
		ray->pwall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->pwall_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_height = (int)(720 / ray->pwall_dist);
	ray->draw_start = (-ray->line_height / 2) + 360 + ray->v_offset;
	ray->draw_end = (ray->line_height / 2) + 360 + ray->v_offset;
	ray_fix_line(ray, a);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= 720)
		ray->draw_end = 719;
	if (ray->side == 0)
		ray->wall_x = cb->player.origin.y + ray->pwall_dist * ray->dir.y;
	else
		ray->wall_x = cb->player.origin.x + ray->pwall_dist * ray->dir.x;
	ray->wall_x -= floorf(ray->wall_x);
}

void	ray_hit_fix(t_ray *ray, int a, int *y)
{
	ray->entity = ray->data[ray->map.y][ray->map.x];
	ray->hit = 1;
	if (ent_is_perks(ray->entity)
		|| ent_is_trap(ray->entity))
	{
		if (a && *y >= 1)
		{
			*y -= 1;
			ray->hit = 0;
		}
		else if (!a)
		{
			++ray->n;
			ray->hit = 0;
		}
	}
}

void	ray_dda_hit(t_ray *ray, int a)
{
	int		i;
	int		y;

	i = 0;
	y = ray->n;
	while (!ray->hit && i < 2000)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (bg_isinmap((t_vec2){ray->map.x, ray->map.y})
				&& ent_is_solid(ray->data[ray->map.y][ray->map.x]))
			ray_hit_fix(ray, a, &y);
		++i;
	}
}

void	ray_dda_step(t_ray *ray, t_player *p)
{
	ray->step.x = 1;
	ray->side_dist.x
		= (ray->map.x + 1.0 - p->origin.x) * ray->delta_dist.x;
	ray->step.y = 1;
	ray->side_dist.y
		= (ray->map.y + 1.0 - p->origin.y) * ray->delta_dist.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (p->origin.x - ray->map.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (p->origin.y - ray->map.y) * ray->delta_dist.y;
	}
}
