/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:58:55 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:31:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static t_prim	r_rectangle(t_vec4 p, __uint32_t col)
{
	t_prim	c;

	c = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&c, (t_vec2){p.x, p.y});
	ml_vertex(&c, (t_vec2){p.x + p.z, p.y});
	ml_vertex(&c, (t_vec2){p.x + p.z, p.y + p.w});
	ml_vertex(&c, (t_vec2){p.x, p.y + p.w});
	ml_color(&c, col);
	return (c);
}

static void	rotate_point(t_vec2 *p, float cx, float cy, float angle)
{
	float	s;
	float	c;
	float	x_new;
	float	y_new;

	s = sinf(angle);
	c = cosf(angle);
	x_new = (p->x - cx) * c - (p->y - cy) * s + cx;
	y_new = (p->x - cx) * s + (p->y - cy) * c + cy;
	p->x = x_new;
	p->y = y_new;
}

void	draw_arrow(t_player *player, t_vec2 pos)
{
	t_vec2	p1;
	t_vec2	p2;
	t_vec2	p3;
	t_vec3f	arr;
	t_prim	arrow;

	arr = (t_vec3f){12, 8, 0};
	arr.z = atan2f(player->dir.y, player->dir.x) + 1.570796f;
	pos.x += 16;
	pos.y += 16;
	p1 = (t_vec2){pos.x, pos.y - arr.x};
	p2 = (t_vec2){pos.x - arr.y, pos.y + arr.y};
	p3 = (t_vec2){pos.x + arr.y, pos.y + arr.y};
	rotate_point(&p1, pos.x, pos.y, arr.z);
	rotate_point(&p2, pos.x, pos.y, arr.z);
	rotate_point(&p3, pos.x, pos.y, arr.z);
	arrow = ml_begin(ML_PRIM_TRIANGLES);
	ml_vertex(&arrow, p1);
	ml_vertex(&arrow, p2);
	ml_vertex(&arrow, p3);
	ml_color(&arrow, 0xFFFF00);
	ml_savemesh(&arrow, "minimap");
	ml_end(&arrow);
}

void	init_minimap(int lm)
{
	t_shaders	*sh;
	t_prim		c;

	sh = get_img("minimap");
	if (sh)
	{
		if (sh->img.width != (32 * (lm * 2)) + 9)
			resize_img("minimap", (32 * (lm * 2)) + 9, (32 * (lm * 2)) + 8);
		fill_img_color(&sh->img, 0x030303);
		c = r_rectangle((t_vec4){2, 2, (32 * (lm * 2)) + 5,
				(32 * (lm * 2)) + 4}, 0);
		ml_settexture(&c, "/gold_border.xpm");
		ml_size(&c, 4);
		ml_setmode(&c, ML_MODE_LINE);
		ml_savemesh(&c, "minimap");
		ml_end(&c);
	}
}
