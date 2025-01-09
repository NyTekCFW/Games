/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:35:36 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/25 15:24:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	pause_status(int ks, t_core *core)
{
	if (!get_cmd(core)->is_open && ks == XK_space
		&& get_status(core) < status_cmd && get_status(core) > status_main)
	{
		if (get_status(core) == status_playing)
		{
			set_key_status(core, 0);
			set_status(core, status_pause);
			draw_pause(core, 0);
			render_submenu(core);
		}
		else
			ui_resume_button(core);
	}
}

static int	hook_keyboard(int ks, t_core *core)
{
	if (get_game(core)->stop_proc)
		return (0);
	pause_status(ks, core);
	if (get_status(core) == status_playing)
		get_hook(core)->binds = binds_resume;
	else if (get_status(core) == status_pause)
		get_hook(core)->binds = binds_pause;
	else if (get_status(core) == status_cmd)
		get_hook(core)->binds = binds_cmd;
	else
		get_hook(core)->binds = binds_main;
	if (get_hook(core)->binds)
		core->hook.binds(ks, core);
	return (1);
}

static int	hook_mouse(int ks, int x, int y, t_core *core)
{
	t_uibutton	btn;

	if (get_game(core)->stop_proc)
		return (0);
	if (get_status(core) == status_playing)
	{
		if (!get_client(core)->is_meleeing && ks == m_left_click)
		{
			get_client(core)->is_meleeing = 1;
			next_anim(core, a_player_melee);
			playsound("link_attack", 0, 0, 1);
			try_attack(core);
		}
		return (0);
	}
	if (button_click(ks, vec2t(x, y), core, &btn))
	{
		if (btn.call_func)
			btn.call_func(core);
	}
	return (0);
}

static int	hook_render(t_core *core)
{
	t_anim	*gm;
	clock_t	cpu;

	if (get_game(core)->stop_proc)
		return (0);
	death_player(core);
	if (get_status(core) != status_playing)
		return (1);
	gm = get_anim(core);
	cpu = clock();
	while (clock() < gm->frame[f_ellipse])
		;
	check_anim(core);
	browse_map_rng(core, a_print);
	browse_map_rng(core, print_map);
	gm->frame[f_fps] = get_fps(cpu);
	if (gm->frame[f_fps] > 120)
		gm->frame[f_fps] = 120;
	if (flag_status(core, p_info))
		show_info(core);
	gm->frame[f_ellipse] = clock() + 8333;
	return (1);
}

int	win_hook(t_core *core)
{
	mlx_loop_hook(get_mlx(core)->ptr, hook_render, core);
	mlx_hook(get_mlx(core)->win, KeyPress, (1L << 0), hook_keyboard, core);
	mlx_hook(get_mlx(core)->win, KeyRelease, (1L << 1), hook_key_release, core);
	mlx_hook(get_mlx(core)->win, ButtonPress, (1L << 2), hook_mouse, core);
	mlx_hook(get_mlx(core)->win, 17, 0L, win_exit, core);
	system("xset r rate 100 30");
	print_img(core, vec2t(0, 0), "/intro.xpm");
	render_submenu(core);
	playsound("main_menu", 0, 1, 0);
	mlx_loop(get_mlx(core)->ptr);
	mlx_destroy_window(get_mlx(core)->ptr, get_mlx(core)->win);
	win_error(core);
	return (1);
}
