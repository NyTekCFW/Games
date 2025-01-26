/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:22:31 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:22:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_client_move.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/core/parsing.h"
#include "../../includes/bgame/bg_register_trigger.h"
#include "../../includes/game/g_axis.h"

void	_wait(clock_t time)
{
	while (clock() < time)
		;
}

void	_draw_loading(t_screen *screen, t_ml *lx, char *av, int prc)
{
	t_prim	x;

	x = ml_quad((t_vec2){40, 700}, (t_vec2){1200, 6}, 0x030303);
	ml_savemesh(&x, "framework");
	ml_end(&x);
	x = ml_quad((t_vec2){41, 701}, (t_vec2){
			linear_scaling(prc, 0, 100, 1198), 4}, 0xff0000);
	ml_savemesh(&x, "framework");
	ml_end(&x);
	typewritter("framework", av, (t_vec2){40, 660});
	print_img((t_vec2){0, 0}, "clear_window");
	print_img((t_vec2){screen->x, screen->y}, "framework");
	dbg_string(lx, 5, 15, "Booting OpenMLX Engine... Done.");
	dbg_string(lx, 5, 40, "Registering Data... Done.");
	dbg_string(lx, 5, 65, "Registering XPM Files...");
	if (prc >= 50)
		dbg_string(lx, 145, 65, "Done.");
	if (prc >= 75)
		dbg_string(lx, 5, 90, "Register Hook Callback...");
	_wait(clock() + 1000000);
	if (prc == 100)
	{
		dbg_string(lx, 165, 90, "Done.");
		system("pkill paplay");
	}
}

void	display_map_loading(char *av, t_screen *sc, t_ml *lx)
{
	t_shaders	*sh;

	sh = get_img("framework");
	if (!sh)
		return ;
	playsound("loading_map", 0, 0, 0);
	fill_img_color(&sh->img, 0x2f2f2f);
	_draw_loading(sc, lx, av, 25);
	lx->refresh = 1;
	bg_register_xpm();
	_draw_loading(sc, lx, av, 50);
	if (*(int *)getvar("cg_mouse_fix"))
	{
		mlx_mouse_move(lx->ptr, lx->win, lx->width / 2, lx->height / 2);
		mlx_mouse_hide(lx->ptr, lx->win);
	}
	_draw_loading(sc, lx, av, 75);
	lx->render_callback = display;
	lx->mouse_p_callback = pressed_key;
	lx->mouse_m_callback = mouse_move;
	lx->end_hook_callback = g_exit;
	_draw_loading(sc, lx, av, 100);
	playsound("game_start", 0, 0, 0);
	start_hook();
}
