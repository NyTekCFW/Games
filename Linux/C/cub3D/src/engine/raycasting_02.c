/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:25:25 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:29 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static t_shaders	*get_perks_texture(t_ray *ray)
{
	if (ray->entity == '[')
		return (get_img("/juggernog.xpm"));
	else if (ray->entity == ']')
		return (get_img("/doubletap.xpm"));
	else if (ray->entity == '{')
		return (get_img("/speed_cola.xpm"));
	else if (ray->entity == '}')
		return (get_img("/quick_regen.xpm"));
	else if (ray->entity == '+')
		return (get_img("/doubletap.xpm"));
	else if (ray->entity == 'P')
		return (get_img("/packapunch.xpm"));
	return (NULL);
}

static t_shaders	*get_walls_texture(t_ray *ray)
{
	if (ray->entity == 'K')
		return (ray->texture[TEX_DOOR_CLOSE]);
	else if (ray->entity == 'T')
		return (ray->texture[TEX_DOOR_CLOSE]);
	else if (!ray->side)
	{
		if (ray->dir.x < 0)
			return (ray->texture[TEX_WALL_EAST]);
		else
			return (ray->texture[TEX_WALL_WEST]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (ray->texture[TEX_WALL_NORTH]);
		else
			return (ray->texture[TEX_WALL_SOUTH]);
	}
	return (NULL);
}

void	draw_walls(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh[2];

	sh[0] = ray->texture[TEX_RENDER];
	sh[1] = get_walls_texture(ray);
	if (sh[0] && sh[1] && !ent_is_perks(ray->entity))
		draw_ents(ray, (t_vec3){x, 0, 1}, sh, p);
}

void	draw_fire(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh[2];
	int			i;

	sh[0] = ray->texture[TEX_RENDER];
	sh[1] = get_anim_img(WORLD_ANIM_FIRE, "fire_000");
	if (sh[0] && sh[1] && !ent_is_perks(ray->entity))
	{
		i = ray->var_shadow;
		ray->var_shadow = 0;
		draw_ents(ray, (t_vec3){x, 0, 0}, sh, p);
		ray->var_shadow = i;
	}
}

void	draw_perks(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh[2];

	sh[0] = ray->texture[TEX_RENDER];
	sh[1] = get_perks_texture(ray);
	if (sh[0] && sh[1] && ent_is_perks(ray->entity))
		draw_ents(ray, (t_vec3){x, 0, 0}, sh, p);
}
