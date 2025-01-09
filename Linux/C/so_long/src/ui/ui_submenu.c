/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_submenu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 07:13:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/21 06:49:22 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_submenu	*add_submenu(t_core *core, int id, char *title)
{
	t_submenu	*sub;

	sub = &core->submenu[id];
	sl_memset(sub, 0, sizeof(t_submenu));
	insert_str(sub->title, title, 32);
	sub->call_param = core;
	sub->defined = 1;
	return (sub);
}

static void	add_button(t_submenu *sub, char *txt, t_ui *ui, void (*func)())
{
	t_uibutton	*btn;

	btn = &sub->button[sub->btn_count];
	insert_str(btn->text, txt, 32);
	btn->pressed = 0;
	btn->call_func = func;
	btn->defined = 1;
	sl_memcpy(&btn->ui, ui, sizeof(t_ui));
	ui->y += 25;
	sub->btn_count++;
}

void	init_submenu(t_core *core)
{
	int			grey;
	t_ui		ui;
	t_submenu	*sub;

	grey = get_color(core)->grey;
	sub = add_submenu(core, status_main, "Main Menu");
	ui = ui_add(vec2t(5, 20), vec2t(100, 20), grey);
	add_button(sub, "Play Game", &ui, ui_play_button);
	add_button(sub, "Leaderboards", &ui, show_leaderboard);
	add_button(sub, "Quit Game", &ui, cmd_quit_f);
	sub = add_submenu(core, status_pause, "Pause Menu");
	ui = ui_add(vec2t(5, 20), vec2t(100, 20), grey);
	add_button(sub, "Resume Game", &ui, ui_resume_button);
	add_button(sub, "Leaderboards", &ui, show_leaderboard);
	add_button(sub, "Quit Game", &ui, cmd_quit_f);
}

void	render_submenu(t_core *core)
{
	t_vec2		pos;
	t_uibutton	*btn;
	int			i;

	if (get_status(core) == status_playing)
		return ;
	if (!get_submenu(core)->defined)
		return ;
	i = 0;
	while (i < 5)
	{
		btn = &get_submenu(core)->button[i];
		if (btn && btn->defined)
		{
			pos = vec2t(btn->ui.x, btn->ui.y);
			print_img(core, pos, "/ui_button");
			r_centertext(core, btn->ui, btn->text);
		}
		i++;
	}
}
