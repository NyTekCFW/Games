/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:48:32 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/08 08:43:38 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static t_shaders	*get_mm_icon(char c)
{
	if (c == '1')
		return (get_img("/mm_wall.xpm"));
	if (c == '[')
		return (get_img("perks_001"));
	if (c == ']')
		return (get_img("perks_002"));
	if (c == '{')
		return (get_img("perks_003"));
	if (c == '}')
		return (get_img("perks_000"));
	if (c == '+')
		return (get_img("/mm_ammo.xpm"));
	if (c == 'D')
		return (get_anim_img(WORLD_ANIM_MM_FIRE, "mm_fire_000"));
	if (c == 'K')
		return (get_img("/mm_door_closed.xpm"));
	if (c == 'T')
		return (get_img("/mm_door_open.xpm"));
	if (c == 'P')
		return (get_img("/mm_pap.xpm"));
	if (c == 'g')
		return (get_img("/mm_ground.xpm"));
	return (NULL);
}

static void	add_mm_item(t_vec2 u, char c)
{
	t_shaders	*mm;
	t_shaders	*item;

	item = get_mm_icon(c);
	mm = get_img("minimap");
	if (mm && item)
	{
		u.x = 4 + (u.x * 32);
		u.y = 4 + (u.y * 32);
		merge_img(mm, item, u);
	}
}

void	build_minimap(t_vec2 u, t_vec2 p, int lm, t_cb *cub)
{
	char	c;
	t_vec2	w;

	w = (t_vec2){0, 0};
	while (u.y < lm)
	{
		w.x = 0;
		u.x = -lm;
		while (u.x < lm)
		{
			if (bg_isinmap((t_vec2){p.x + u.x, p.y + u.y}))
			{
				c = cub->map_data.map[p.y + u.y][p.x + u.x];
				if (c && c != ' ')
				{
					add_mm_item(w, 'g');
					add_mm_item(w, c);
				}
			}
			++w.x;
			++u.x;
		}
		++w.y;
		++u.y;
	}
}

void	draw_minimap(void)
{
	t_cb		*cub;
	t_vec2		u;
	t_vec2		p;
	int			lm;
	t_shaders	*sh[2];

	cub = g_cub(ACT_GET);
	sh[0] = get_img("framework");
	sh[1] = get_img("minimap");
	if (cub && sh[0] && sh[1])
	{
		lm = 2 + *(int *)getvar("cg_minimap_zoom");
		init_minimap(lm);
		u = (t_vec2){-lm, -lm};
		p = (t_vec2){(int)cub->player.origin.x, (int)cub->player.origin.y};
		build_minimap(u, p, lm, cub);
		draw_arrow(&cub->player, (t_vec2){6 + (lm * 32), 6 + (lm * 32)});
		merge_img(sh[0], sh[1], (t_vec2){4, 4});
		draw_compass();
	}
}
