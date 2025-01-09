/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/26 20:56:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	register_images(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		create_img((t_ui){lx->width, lx->height, 0},
			fill_img_color, "framework");
		register_img("./textures/fonts/monospace_ttf.xpm");
		split_image("/monospace_ttf.xpm", "monospace_", 32, 0);
	}
}

void	pressed_key(int ks, int x, int y, t_ml *lx)
{
	t_menu	*menu;

	(void)lx;
	(void)ks;
	menu = dbg_menu(ACT_GET);
	if (menu && menu->_open)
		dbg_click((t_vec2){x, y});
}

void opendebug(void)
{
	t_menu	*menu;

	menu = dbg_menu(ACT_GET);
	if (menu)
	{
		menu->_open = !menu->_open;
		set_keycode_status(XK_p, 0);
	}
}


void	render_frame(t_ml *lx)
{
	t_menu			*menu;

	(void)lx;
	menu = dbg_menu(ACT_GET);
	if (lx)
	{
		fill_shader_color("framework", 0);
		draw_game();
		print_img((t_vec2){0}, "framework");
		if (menu && menu->_open)
			dbg_display_menu(lx);
	}
}

void update_game(t_ml *lx)
{
	lx->game.b_origin.x += lx->game.b_velocity.x;
	lx->game.b_origin.y += lx->game.b_velocity.y;
}

void	render(t_ml *lx)
{
	static clock_t	last_render = 0;
	static clock_t	last_update = 0;
	static clock_t	last_player_cmd = 0;
	clock_t			currentTime;
	int				elapsedTime;
	int				waittime;
	int				i;

	if (lx)
	{
		currentTime = clock();
		elapsedTime = (currentTime - last_render) * 1000 / CLOCKS_PER_SEC;
		if ((currentTime - last_player_cmd) * 1000 / CLOCKS_PER_SEC >= (1000 / 144) * (lx->game.timescale))
		{
			last_player_cmd = currentTime;
			i = -1;
			while (++i < *get_key_count())
				keynum_execute(i);
		}
		if ((currentTime - last_update) * 1000 / CLOCKS_PER_SEC >= (1000 / 90) * (lx->game.timescale))
		{
			last_update = currentTime;
			update_game(lx);
		}
		if (elapsedTime >= (1000 / lx->game.fps) * (lx->game.timescale))
		{
			last_render = currentTime;
			render_frame(lx);
		}
		waittime = (currentTime - last_update) * 1000 / CLOCKS_PER_SEC;
		if ((1000 / lx->game.fps) > waittime)
			waittime = (1000 / lx->game.fps) - waittime;
		else
			waittime = 0;
		if (waittime > 0)
			usleep(waittime);
	}
}

void	move_p1_up(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		lx->game.p_origin[PLAYER_1].y -= 4;
		if (lx->game.p_origin[PLAYER_1].y <= lx->game.p_bbox_rng[PLAYER_1].y - 15)
			lx->game.p_origin[PLAYER_1].y = lx->game.p_bbox_rng[PLAYER_1].y - 15;
	}
}

void	move_p1_down(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		lx->game.p_origin[PLAYER_1].y += 4;
		if (lx->game.p_origin[PLAYER_1].y >= (lx->game.p_bbox_rng[PLAYER_1].y + ((lx->game.p_bbox_rng[PLAYER_1].w / 3) * 2)))
			lx->game.p_origin[PLAYER_1].y = (lx->game.p_bbox_rng[PLAYER_1].y + ((lx->game.p_bbox_rng[PLAYER_1].w / 3) * 2));
	}
}

void	move_p0_up(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		lx->game.p_origin[PLAYER_0].y -= 4;
		if (lx->game.p_origin[PLAYER_0].y <= lx->game.p_bbox_rng[PLAYER_0].y - 15)
			lx->game.p_origin[PLAYER_0].y = lx->game.p_bbox_rng[PLAYER_0].y - 15;
	}
}

void	move_p0_down(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		lx->game.p_origin[PLAYER_0].y += 4;
		if (lx->game.p_origin[PLAYER_0].y >= (lx->game.p_bbox_rng[PLAYER_0].y + ((lx->game.p_bbox_rng[PLAYER_0].w / 3) * 2)))
			lx->game.p_origin[PLAYER_0].y = (lx->game.p_bbox_rng[PLAYER_0].y + ((lx->game.p_bbox_rng[PLAYER_0].w / 3) * 2));
	}
}

// Setup Exemple
int	main(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_INIT);
	if (lx)
	{
		lx->purge_color = 0x7f7f7f;
		if (lx->set_win_size(640, 400) && lx->make_window("Pong - Game"))
		{
			register_images();
			init_data();
			add_keycode(XK_p, opendebug);
			add_keycode(XK_o, move_p1_up);
			add_keycode(XK_l, move_p1_down);
			add_keycode(XK_e, move_p0_up);
			add_keycode(XK_d, move_p0_down);
			lx->render_callback = render;
			lx->mouse_p_callback = pressed_key;
			start_hook();
			dbg_menu(ACT_FREE);
			lx->quit_window();
		}
	}
}
