/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_register_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:46:31 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:32:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/core/parsing.h"

static void	register_huds(void)
{
	register_img("./textures/huds/dpad.xpm");
	register_img("./textures/huds/dpad_bar.xpm");
	register_img("./textures/huds/hud_score.xpm");
	register_img("./textures/huds/crosshair_v.xpm");
	register_img("./textures/huds/crosshair_h.xpm");
	register_img("./textures/huds/perks.xpm");
	register_img("./textures/huds/gold_border.xpm");
	register_img("./textures/huds/mm_ground.xpm");
	register_img("./textures/huds/mm_pap.xpm");
	register_img("./textures/huds/mm_fire.xpm");
	register_img("./textures/huds/mm_wall.xpm");
	register_img("./textures/huds/mm_ammo.xpm");
	register_img("./textures/huds/mm_door_closed.xpm");
	register_img("./textures/huds/mm_door_open.xpm");
	split_image("/perks.xpm", "perks_", 32, 0);
	split_image("/mm_fire.xpm", "mm_fire_", 32, 0);
	register_img("./textures/walls/juggernog.xpm");
	register_img("./textures/walls/speed_cola.xpm");
	register_img("./textures/walls/quick_regen.xpm");
	register_img("./textures/walls/doubletap.xpm");
	register_img("./textures/zombies.xpm");
	split_image("/zombies.xpm", "zombie_", 256, 0);
}

static void	register_walls(void)
{
	t_file		*f;
	t_shaders	**textures;

	textures = get_textures();
	f = get_parsing_file(ACT_GET);
	if (textures && f)
	{
		register_img(f->texture_no);
		register_img(f->texture_so);
		register_img(f->texture_we);
		register_img(f->texture_ea);
		textures[TEX_WALL_SOUTH] = get_img(xstrchr(f->texture_so, '/'));
		textures[TEX_WALL_NORTH] = get_img(xstrchr(f->texture_no, '/'));
		textures[TEX_WALL_EAST] = get_img(xstrchr(f->texture_ea, '/'));
		textures[TEX_WALL_WEST] = get_img(xstrchr(f->texture_we, '/'));
	}
	register_img("./textures/walls/door_closed.xpm");
	register_img("./textures/walls/fire.xpm");
	register_img("./textures/walls/packapunch.xpm");
	register_img("./textures/xzm.xpm");
	split_image("/fire.xpm", "fire_", 256, 0);
}

static void	register_wpns_textures(void)
{
	int				i;
	t_weapon_data	*wpns;

	wpns = get_wpn_data();
	if (wpns)
	{
		register_img("./textures/weapon/M1911_reload_1.xpm");
		register_img("./textures/weapon/M1911_reload_2.xpm");
		register_img("./textures/weapon/M1911_reload_3.xpm");
		register_img("./textures/weapon/M1911_reload_4.xpm");
		register_img("./textures/weapon/M1911_reload_5.xpm");
		register_img("./textures/weapon/M1911_reload_6.xpm");
		register_img("./textures/weapon/M1911_fire.xpm");
		i = split_image("/M1911_idle_walk.xpm", "M1911_walk_", 640, 0);
		wpns[WPN_M1911].frame[WPN_FRAME_WALK] = i - 1;
		i = split_image("/M1911_reload_1.xpm", "M1911_reload_", 640, 0);
		i = split_image("/M1911_reload_2.xpm", "M1911_reload_", 640, i);
		i = split_image("/M1911_reload_3.xpm", "M1911_reload_", 640, i);
		i = split_image("/M1911_reload_4.xpm", "M1911_reload_", 640, i);
		i = split_image("/M1911_reload_5.xpm", "M1911_reload_", 640, i);
		i = split_image("/M1911_reload_6.xpm", "M1911_reload_", 640, i);
		wpns[WPN_M1911].frame[WPN_FRAME_RELOAD] = i - 1;
		i = split_image("/M1911_fire.xpm", "M1911_fire_", 640, 0);
		wpns[WPN_M1911].frame[WPN_FRAME_FIRE] = i - 1;
	}
}

void	clear_parsing(void)
{
	int		i;
	t_file	*f;

	i = 0;
	f = get_parsing_file(ACT_GET);
	if (f)
	{
		xfree((void **)&f->content);
		while (i < f->total_line)
			xfree((void **)&f->map[i++]);
		xfree((void **)&f->map);
		xfree((void **)&f->texture_no);
		xfree((void **)&f->texture_so);
		xfree((void **)&f->texture_ea);
		xfree((void **)&f->texture_we);
		get_parsing_file(ACT_FREE);
	}
}

void	bg_register_xpm(void)
{
	t_ml			*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		register_huds();
		register_walls();
		register_img("./textures/weapon/M1911_idle_walk.xpm");
		register_wpns_textures();
		bg_attibute_xpm();
		clear_parsing();
	}
}
