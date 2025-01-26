/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:38:22 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/26 19:20:28 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct ray_s
{
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	__uint32_t	color_ceil;
	__uint32_t	color_floor;
	int			n;
	double		camera;
	double		pwall_dist;
	float		wall_x;
	t_vec2f		dir;
	t_vec2f		side_dist;
	t_vec2f		delta_dist;
	t_vec2		map;
	t_vec2		step;
	t_vec2		amp;
	t_shaders	**texture;
	char		**data;
	double		var_shadow_radius;
	double		var_aspect;
	double		var_lightradius;
	int			var_shadow;
	int			var_light;
	__uint32_t	var_colorlight;
	float		v_offset;
	__int8_t	entity;
}	t_ray;

void		draw_ceiling(int x, t_ray *ray, t_player *p);
void		draw_floor(int x, t_ray *ray, t_player *p);
void		draw_walls(int x, t_ray *ray, t_player *p);
void		draw_fire(int x, t_ray *ray, t_player *p);
void		draw_perks(int x, t_ray *ray, t_player *p);
void		draw_ents(t_ray *r, t_vec3 u, t_shaders *sh[], t_player *p);
void		flashlight_move(t_vec2 *u);
void		flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c);
void		raycast_env(void);
__uint32_t	get_shadow(__uint32_t c, float dist, int enabled);
t_vec2		*get_move_render(void);

void		ray_line(t_ray *ray, void *cub, int a);
void		ray_hit_fix(t_ray *ray, int a, int *y);
void		ray_dda_hit(t_ray *ray, int a);
void		ray_dda_step(t_ray *ray, t_player *p);

int			ent_is_solid(char c);
int			ent_is_trigger(char c);
int			ent_is_trap(char c);
int			ent_is_ground(char c);
int			ent_is_valid(char c);
int			ent_is_perks(char c);
#endif