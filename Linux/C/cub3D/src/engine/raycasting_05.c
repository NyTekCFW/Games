/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_05.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:17:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:06:44 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	display_ray(int x, int a, t_ray *ray, t_player *p)
{
	if (a)
	{
		draw_fire(x, ray, p);
		draw_perks(x, ray, p);
	}
	else
	{
		draw_walls(x, ray, p);
		draw_floor(x, ray, p);
		draw_ceiling(x, ray, p);
	}
}

static void	init_ray(t_ray *ray, t_cb *cub, int x, int a)
{
	t_player	*player;

	player = &cub->player;
	ray->camera = ((2 * x) / (float)1280 - 1)
		* (tanf(ray->var_aspect) * 1.777777778);
	ray->dir.x = player->dir.x + player->plane.x * ray->camera;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera;
	ray->map = (t_vec2){(int)player->origin.x, (int)player->origin.y};
	ray->delta_dist = (t_vec2f){fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
	ray->hit = 0;
	ray_dda_step(ray, player);
	ray_dda_hit(ray, a);
	ray_line(ray, cub, a);
	if (ray->draw_end >= 0 && ray->draw_end < 720)
		display_ray(x, a, ray, player);
}

/// @brief using raycasting to build the environnement based on player view 

static int	ray_settings(t_ray *ray, t_cb *cub)
{
	static t_vec3f	c = {1, 1, 1};

	ray->var_shadow = *(int *)getvar("cg_shadow_enable");
	ray->var_shadow_radius = *(double *)getvar("bg_shadow_radius");
	ray->var_aspect = *(double *)getvar("cg_aspect") / 2;
	ray->var_lightradius = *(double *)getvar("bg_flashlight_radius");
	ray->var_colorlight = *(__uint32_t *)getvar("bg_flashlight_color");
	ray->var_light = *(int *)getvar("cg_flashlight_enable");
	ray->texture = cub->texture;
	ray->v_offset = tanf(cub->player.vangle) * 360;
	ray->data = cub->map_data.map;
	ray->color_ceil = cub->map_data.color_ceil;
	ray->color_floor = cub->map_data.color_floor;
	cycle_rainbow_color(&c, 1.5);
	cub->map_data.color_rgb = ((int)(c.x * 255.f) << 16)
		| ((int)(c.y * 255.f) << 8) | (int)(c.z * 255.f);
	if (*(int *)getvar("cg_rgb_ceil"))
		ray->color_ceil = cub->map_data.color_rgb;
	if (*(int *)getvar("cg_rgb_floor"))
		ray->color_floor = cub->map_data.color_rgb;
	flashlight_move(get_move_render());
	ray->amp = *get_move_render();
	return (ray->texture[TEX_RENDER] != 0);
}

void	raycast_env(void)
{
	t_ray	ray;
	t_cb	*cub;
	int		x;

	x = 0;
	cub = g_cub(ACT_GET);
	if (cub)
	{
		xmemset(&ray, 0, sizeof(t_ray));
		if (ray_settings(&ray, cub))
		{
			fill_img_color(&ray.texture[TEX_RENDER]->img, ray.color_ceil);
			while (x < 1280)
			{
				ray.n = 0;
				init_ray(&ray, cub, x, 0);
				if (ray.hit)
				{
					while (ray.n)
						init_ray(&ray, cub, x, ray.n--);
				}
				++x;
			}
		}
	}
}
