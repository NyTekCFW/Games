/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_color_picker_03.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:41:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:15:58 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static void	_asm_cbar(t_shaders *sh, t_shaders *bar, t_vec4 u, __uint32_t *cl)
{
	t_vec2		w;
	t_vec2		v;
	__uint32_t	c;

	if (sh && bar)
	{
		v = (t_vec2){u.z, u.w};
		w = (t_vec2){u.x, u.y};
		if (u.y >= 4 && u.y <= 10 && u.x >= 4 && u.x <= 10)
		{
			if (get_px_color(&sh->img, w) != 0xFFFFFF)
			{
				c = get_px_color(&bar->img, v);
				set_color(&sh->img, get_px_adr(&sh->img, w), c);
				*cl = c;
			}
		}
	}
}

void	cpicker_cursor_bar(char *name, t_vec2 v, __uint32_t *cl)
{
	t_shaders	*sh;
	t_shaders	*bar;
	t_shaders	*c;
	t_vec4		u;

	bar = get_img("cpicker_bar");
	if (name && bar && cl)
	{
		fill_shader_color(name, 0);
		sh = get_img(name);
		c = get_img("cpicker_cursor");
		if (sh && c)
		{
			merge_img(sh, c, (t_vec2){0});
			u = (t_vec4){-1, -1, v.x, v.y};
			while (++u.y < sh->img.height)
			{
				u.x = -1;
				while (++u.x < sh->img.width)
					_asm_cbar(sh, bar, u, cl);
			}
		}
	}
}

static void	_asm_cursor(t_shaders *sh, t_vec2 u, __uint32_t c)
{
	if (sh)
	{
		if (u.y >= 4 && u.y <= 10 && u.x >= 4 && u.x <= 10)
		{
			if (get_px_color(&sh->img, u) != 0xFFFFFF)
				set_color(&sh->img, get_px_adr(&sh->img, u), c);
		}
	}
}

void	cpicker_cursor(char *name, __uint32_t c)
{
	t_shaders	*sh;
	t_shaders	*cs;
	t_vec2		u;

	if (name)
	{
		fill_shader_color(name, 0);
		sh = get_img(name);
		cs = get_img("cpicker_cursor");
		if (sh && cs)
		{
			merge_img(sh, cs, (t_vec2){0});
			u = (t_vec2){-1, -1};
			while (++u.y < sh->img.height)
			{
				u.x = -1;
				while (++u.x < sh->img.width)
					_asm_cursor(sh, u, c);
			}
		}
	}
}
/*
Build and export an rainbow bar 
with fade effect
void color_picker_init_bar(void)
{
	__uint32_t clist[7];
	__uint32_t c;
	t_vec2 u;
	t_shaders *sh;
	int segw;
	float d;
	int segi;

	sh = get_img("color_picker_bar");
	u = (t_vec2){-1, -1};
	fill_img_color(&sh->img, 0);
	xmemcpy(clist, (__uint32_t[]){0x00FF0000, 0x00FFFF00,
	0x0000FF00, 0x0000FFFF, 0x000000FF, 0x00FF00FF,
	0x00FF0000}, sizeof(__uint32_t) * 7);
	segw = (sh->img.width) / 6;
	while (++u.y < sh->img.height)
	{
		u.x = 0;
		while (++u.x < sh->img.width)
		{
			segi = u.x / segw;
			d = (float)u.x / segw;
			if ((d == (float)segi))
			{
				d -= 0.01f;
				segi -= 1;
			}
			c = gradient(clist[segi], clist[segi + 1], d);
			if (is_valid_color(c))
				set_color(&sh->img, get_px_adr(&sh->img, u), c);
		}
	}
	export_img("color_picker_bar");
	exit(1);
}*/