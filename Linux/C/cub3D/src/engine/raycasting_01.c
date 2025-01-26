/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:21:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:25 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

void	flashlight_move(t_vec2 *u)
{
	static t_vec2	t = {1, -1};

	u->x += t.x;
	u->y += t.y;
	if (u->x >= 8 || u->x <= -8)
		t.x *= -1;
	if (u->y >= 5 || u->y <= -5)
		t.y *= -1;
}

void	flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c)
{
	double	xdist;
	t_vec2f	center;
	double	a;
	double	radius;

	if (sh && ray->var_light)
	{
		radius = ray->var_lightradius;
		center = (t_vec2f){(sh->img.width / 2) + ray->amp.x,
			(sh->img.height / 2) + ray->amp.y};
		xdist = dist(center, (t_vec2f){v.x, v.y});
		if (xdist <= radius + ray->pwall_dist)
		{
			a = expf(-0.05 * xdist) + (0.7 / (ray->pwall_dist + 1));
			if (xdist > radius)
				a *= 1.0 - (xdist - radius) / (radius / 2.0);
			a = fmaxf(0.0, fminf(a, 1.0));
			set_color(&sh->img, get_px_adr(&sh->img, v),
				blend_colors(c, ray->var_colorlight, a));
		}
	}
}

void	draw_ceiling(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;
	__uint32_t	c;
	float		a;

	sh = ray->texture[TEX_RENDER];
	if (sh)
	{
		y = ray->draw_start;
		a = ((720 * ((0.7f + p->vangle) / 1.6f)));
		while (--y >= 0)
		{
			c = get_shadow(ray->color_ceil, ((float)y / a) * \
					ray->var_shadow_radius, ray->var_shadow);
			if (c != ray->color_ceil)
				set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, ray->color_ceil);
		}
	}
}

void	draw_floor(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	__uint32_t	c[2];
	int			y;

	sh = ray->texture[TEX_RENDER];
	if (sh)
	{
		y = sh->img.height;
		while (--y >= ray->draw_end)
		{
			c[0] = ray->color_floor;
			c[1] = get_shadow(c[0], (1 - ((float)y / 720.0f))
					* ray->var_shadow_radius, ray->var_shadow);
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c[1]);
			ray->pwall_dist = 1 + p->vangle;
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, c[0]);
		}
	}
}
