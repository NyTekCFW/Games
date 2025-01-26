/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:20:35 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:41:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_client_script.h"

void	dbg_togglemenu(void)
{
	t_menu	*menu;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	menu = dbg_menu(ACT_GET);
	if (menu && lx)
	{
		menu->_open = !menu->_open;
		set_keycode_status(XK_p, 0);
		if (menu->_open)
		{
			mlx_mouse_show(lx->ptr, lx->win);
			start_pause();
		}
		else if (!menu->_open)
		{
			stop_pause();
			if (*(int *)getvar("cg_mouse_fix"))
				mlx_mouse_hide(lx->ptr, lx->win);
		}
		lx->purge_window();
	}
}

static void	_addopts(t_cb *cub)
{
	dbg_add_slider("Floor Color", OPT_INT, \
		&cub->map_data.color_floor, (t_vec2f){0, (double)0xFFFFFF});
	dbg_add_slider("Ceil Color", OPT_INT, \
		&cub->map_data.color_ceil, (t_vec2f){0, (double)0xFFFFFF});
	dbg_add_slider("Brightness :", OPT_DOUBLE,
		&cub->var.bg_brightness.dvalue, (t_vec2f){0.0f, 1.5f});
}

static void	_addvar(void)
{
	dbg_add_bool("Rainbow Ceil : ", getvar("cg_rgb_ceil"));
	dbg_add_bool("Rainbow Floor : ", getvar("cg_rgb_floor"));
	dbg_add_bool("Mouse Fix (libx Leak!)", getvar("cg_mouse_fix"));
	dbg_add_bool("Enable Shadow : ", getvar("cg_shadow_enable"));
	dbg_add_bool("Enable Flashlight : ", getvar("cg_flashlight_enable"));
	dbg_add_slider("FPS : ", OPT_INT, getvar("com_maxfps"), (t_vec2f){15, 144});
	dbg_add_slider("Timescale : ", OPT_DOUBLE, getvar("com_timescale"),
		(t_vec2f){0.05f, 2.0f});
	dbg_add_slider("Flashlight Color", OPT_INT, getvar("bg_flashlight_color"),
		(t_vec2f){0, (double)0xFFFFFF});
	dbg_add_slider("Speed : ", OPT_DOUBLE, getvar("g_speed"),
		(t_vec2f){0.01f, 0.04f});
	dbg_add_slider("Shadow Radius : ", OPT_DOUBLE, getvar("bg_shadow_radius"),
		(t_vec2f){0.05f, 2.0f});
	dbg_add_slider("Flashlight Radius : ", OPT_DOUBLE,
		getvar("bg_flashlight_radius"), (t_vec2f){40.f, 100.f});
	dbg_add_slider("Aspect Ratio : ", OPT_DOUBLE, getvar("cg_aspect"),
		(t_vec2f){-1.85f, 1.85f});
	dbg_add_slider("Gun x : ", OPT_DOUBLE, getvar("cg_gun_x"),
		(t_vec2f){0.90f, 1.10f});
	dbg_add_slider("Gun y : ", OPT_DOUBLE, getvar("cg_gun_y"),
		(t_vec2f){0.88f, 1.60f});
	dbg_add_slider("Minimap scale : ", OPT_INT, getvar("cg_minimap_zoom"),
		(t_vec2f){0, 8});
}

static void	_addplayer(t_player *user, t_map *data)
{
	dbg_add_bool("God Mode : ", &user->godmode);
	dbg_add_bool("Aimbot : ", &user->aimbot);
	dbg_add_slider("Player ori x", OPT_DOUBLE, &user->origin.x, \
		(t_vec2f){1.1f, 1.1f + data->width});
	dbg_add_slider("Player ori y", OPT_DOUBLE, &user->origin.y, \
		(t_vec2f){1.1f, 1.1f + data->height});
	dbg_add_slider("Player dir x", OPT_DOUBLE, &user->dir.x, \
		(t_vec2f){-2.0, 2.0});
	dbg_add_slider("Player dir y", OPT_DOUBLE, &user->dir.y, \
		(t_vec2f){-2.0, 2.0});
	dbg_add_slider("Player plane x", OPT_DOUBLE, &user->plane.x, \
		(t_vec2f){-2.0, 2.0});
	dbg_add_slider("Player plane y", OPT_DOUBLE, &user->plane.y, \
		(t_vec2f){-2.0, 2.0});
	dbg_add_slider("Player score", OPT_INT, &user->score, \
		(t_vec2f){0, (float)0x7FFFFFFF});
	dbg_add_slider("Player Health", OPT_INT, &user->health, \
		(t_vec2f){0, (float)300});
	dbg_add_slider("Player vangle", OPT_FLOAT, &user->vangle, \
		(t_vec2f){-0.8f, 0.8f});
}

void	init_imgui(void)
{
	t_ml	*lx;
	t_cb	*cub;
	t_menu	*menu;

	menu = dbg_menu(ACT_INIT);
	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	if (lx && cub && menu)
	{
		dbg_add_str("         ImGUI Settings", NULL);
		dbg_add_slider("ImGUI x : ", OPT_INT, &menu->_pos.x, \
			(t_vec2f){0, lx->width});
		dbg_add_slider("ImGUI y : ", OPT_INT, &menu->_pos.y, \
			(t_vec2f){0, lx->height});
		dbg_add_str("         Player Settings", NULL);
		_addplayer(&cub->player, &cub->map_data);
		dbg_add_str("         Dvars Settings", NULL);
		_addvar();
		dbg_add_str("         Others Settings", NULL);
		_addopts(cub);
	}
}
