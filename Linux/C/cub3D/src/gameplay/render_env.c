/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:25:07 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:25:08 by lchiva           ###   ########.fr       */
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

void	display_buffer(t_ml *lx, t_screen *screen)
{
	t_menu		*menu;

	menu = dbg_menu(ACT_GET);
	if (screen && lx)
	{
		brightness_img("framework",
			(float)(*(double *)getvar("bg_brightness")));
		print_img((t_vec2){0, 0}, "clear_window");
		print_img((t_vec2){screen->x, screen->y}, "framework");
		if (menu && menu->_open)
			dbg_display_menu(lx);
	}
}

void	run_game(t_ml *lx)
{
	t_menu	*menu;
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	menu = dbg_menu(ACT_GET);
	if (cub && !cub->stop_handler)
	{
		raycast_env();
		if ((menu && !menu->_open) || !menu)
		{
			running_env_anim();
			run_axis();
			run_user();
		}
		display_game_over();
		display_buffer(lx, &cub->screen);
		if (cub->player.status == USER_DEAD && clock() >= cub->player.deathtime)
			g_exit();
	}
}

clock_t	get_fps(clock_t cpu)
{
	float	s;

	cpu = clock() - cpu;
	s = (double)cpu / 1000000;
	cpu = 1 / s;
	return (cpu);
}

void	_low_config_check(clock_t cpu)
{
	static int	low = 0;
	char		*fps;

	fps = xitoa(get_fps(cpu));
	if (get_fps(cpu) < 14 && low < 10)
	{
		++low;
		if (low >= 10)
		{
			*(int *)getvar("cg_shadow_enable") = 0;
			*(int *)getvar("cg_flashlight_enable") = 0;
			*(int *)getvar("cg_minimap_zoom") = 0;
			*(int *)getvar("com_maxfps") = 15;
			printf("Error\nYour CPU does not have enough power to run ");
			printf("this game at 100%%\nWeak configuration applied\n");
		}
	}
	if (fps)
	{
		typewritter("framework", fps, (t_vec2){1280 - r_textwidth(fps), 0});
		xfree((void **)&fps);
	}
}

void	display(t_ml *lx)
{
	static clock_t	left = 0;
	clock_t			cpu;
	int				maxfps;
	double			timescale;

	if (lx && lx->refresh)
	{
		maxfps = *(int *)getvar("com_maxfps");
		timescale = *(double *)getvar("com_timescale");
		while (clock() < left)
			;
		left = clock() + (CLOCKS_PER_SEC / (30 * timescale));
		execute_keyboard();
		cpu = clock();
		run_game(lx);
		while (clock() < cpu + (CLOCKS_PER_SEC / maxfps))
			;
		_low_config_check(cpu);
	}
}
