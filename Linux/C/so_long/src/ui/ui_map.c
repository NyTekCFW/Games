/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:45:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/17 07:51:40 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	print_map_mov(t_core *core, char *ent, t_vec2 ps)
{
	t_anim	*gm;

	gm = get_anim(core);
	if (*ent == g_fire)
		print_img(core, ps, gm->name[a_fire]);
	else if (*ent == g_exit)
		print_img(core, ps, gm->name[a_exit]);
	else if (*ent == g_axis)
		print_img(core, ps, get_anim(core)->name[a_axis]);
	else if (*ent == g_player)
	{
		get_client(core)->origin = ps;
		get_client(core)->display = 1;
		get_client(core)->dir = kb_down;
		get_client(core)->health = 150;
		*ent = g_ground;
	}
	if (get_client(core)->display)
	{
		if (!get_client(core)->is_meleeing)
			print_img(core, get_client(core)->origin, gm->name[a_player]);
		else
			print_img(core, get_client(core)->origin, "/player_2");
	}
}

static void	browse_map_rng_init(t_core *core, t_vec2 *px, t_vec2 *pxm)
{
	px->x = get_game(core)->map_print.x + 1;
	px->y = get_game(core)->map_print.y;
	pxm->x = px->x + (get_mlx(core)->width / 60);
	pxm->y = px->y + (get_mlx(core)->height / 60);
	if (pxm->x > get_game(core)->map_max.x)
		pxm->x = get_game(core)->map_max.x;
	if (pxm->y > get_game(core)->map_max.y)
		pxm->y = get_game(core)->map_max.y;
}

void	print_map(t_core *core, char *ent, t_vec2 px)
{
	t_vec2	ps;
	t_vec2	sx;
	t_vec4	mi;

	mi = get_game(core)->map_i;
	ps = vec2t(mi.x + (px.x * 60), mi.y + (px.y * 60));
	sx = vec2t(60, 60);
	if (*ent == g_collect)
		print_img(core, ps, "/ui_rupies");
	else if (*ent == g_ground)
		print_img(core, ps, "/ground.xpm");
	else if (*ent == g_wall)
		r_draw_wall(core, ui_add(ps, sx, 0x5F5F5F));
	print_map_mov(core, ent, ps);
}

void	browse_map(t_core *core, void (*func)())
{
	char	**map;
	t_game	*gm;
	t_vec2	px;
	t_vec2	pxm;

	gm = get_game(core);
	map = get_map(core);
	pxm = gm->map_max;
	px = vec2t(0, 0);
	while (!gm->stop_proc && px.y < pxm.y && map && map[px.y])
	{
		px.x = 0;
		while (!gm->stop_proc && px.x < pxm.x && map && map[px.y][px.x])
		{
			if (func)
				func(core, &map[px.y][px.x], px);
			px.x++;
		}
		px.y++;
	}
}

void	browse_map_rng(t_core *core, void (*func)())
{
	char	**map;
	t_game	*gm;
	t_vec2	px;
	t_vec2	psx;
	t_vec2	pxm;

	gm = get_game(core);
	map = get_map(core);
	browse_map_rng_init(core, &px, &pxm);
	while (!gm->stop_proc && px.y < pxm.y && map && map[px.y])
	{
		px.x = gm->map_rng.x;
		while (!gm->stop_proc && px.x < pxm.x && map && map[px.y][px.x])
		{
			psx = px;
			if (get_client(core)->zones.x > 0 || get_client(core)->zones.y > 0)
				psx = vec2t(px.x - gm->map_rng.x, px.y - gm->map_rng.y);
			if (func)
				func(core, &map[px.y][px.x], psx);
			px.x++;
		}
		px.y++;
	}
	gm->map_print.x = smooth_argb(gm->map_print.x, gm->map_rng.x, 1);
	gm->map_print.y = smooth_argb(gm->map_print.y, gm->map_rng.y, 1);
}
