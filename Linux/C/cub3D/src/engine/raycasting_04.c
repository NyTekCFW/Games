/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:26:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:37 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

int	ent_is_perks(char c)
{
	if (c == '{' || c == '}'
		|| c == '[' || c == ']' || c == '+'
		|| c == 'P')
		return (1);
	return (0);
}

static void	_init_tex(t_ray *r, t_vec2 *tex, t_shaders *sh[], float *step)
{
	tex->x = (int)(r->wall_x * (float)(sh[1]->img.width));
	if (r->side == 0 && r->dir.x > 0)
		tex->x = sh[1]->img.width - tex->x - 1;
	if (r->side == 1 && r->dir.y < 0)
		tex->x = sh[1]->img.width - tex->x - 1;
	*step = 1.0 * sh[1]->img.height / r->line_height;
}

void	draw_ents(t_ray *r, t_vec3 u, t_shaders *sh[], t_player *p)
{
	__uint32_t	c[2];
	t_vec2		tex;
	float		step;
	float		pos;

	_init_tex(r, &tex, sh, &step);
	pos = (r->draw_start - (360 + (int)r->v_offset)
			+ r->line_height / (1 + u.z))
		* step;
	u.y = r->draw_start - 1;
	while (++u.y <= r->draw_end)
	{
		tex.y = ((int)pos & (sh[1]->img.height - 1));
		pos += step;
		c[0] = *(__uint32_t *)(sh[1]->img.addr + get_px_adr(&sh[1]->img, tex));
		if (is_valid_color(c[0]))
		{
			c[1] = get_shadow(c[0], (r->pwall_dist / 15)
					* r->var_shadow_radius, r->var_shadow);
			set_color(&sh[0]->img, get_px_adr(&sh[0]->img, (t_vec2){u.x, u.y}),
				c[1]);
			if (p->flashlight == 1)
				flashlight(sh[0], r, (t_vec2){u.x, u.y}, c[0]);
		}
	}
}

t_vec2	*get_move_render(void)
{
	static t_vec2	amp = {0, 0};

	return (&amp);
}

__uint32_t	get_shadow(__uint32_t c, float dist, int enabled)
{
	if (!enabled)
		return (c);
	if (dist >= 1.0)
		c = 0x030303;
	else
		c = blend_colors(c, 0x030303, dist);
	return (c);
}
