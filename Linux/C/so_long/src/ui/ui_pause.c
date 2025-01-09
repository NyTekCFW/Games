/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_pause.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:57:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/26 07:28:47 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	draw_bkg_pause(t_core *core, int bar_rel)
{
	t_vec2	tmp;
	t_vec2	center;

	center = vec2t(core->mlx.width / 2, core->mlx.height / 2);
	tmp = vec2t(center.x - 110, center.y - 32);
	if (!bar_rel)
		print_img(core, tmp, "/ui_pause");
	tmp.y = center.y + 68;
	print_img(core, tmp, "/ui_pause_bar");
}

void	draw_pause_cmds(t_core *core)
{
	t_color	*clr;
	t_vec2	tmp;
	t_vec2	center;

	clr = get_color(core);
	center = vec2t(core->mlx.width / 2, core->mlx.height / 2);
	tmp = vec2t(center.x + 116, center.y - 32);
	print_img(core, tmp, "/ui_pause_cmd");
	tmp = vec2t(center.x + 118, center.y - 20);
	r_drawtext(core, &tmp, clr->green, "Command List :");
	r_drawtext(core, &tmp, clr->white, "god");
	r_drawtext(core, &tmp, clr->white, "quit");
	r_drawtext(core, &tmp, clr->white, "sprint");
	r_drawtext(core, &tmp, clr->white, "showinfo");
	r_drawtext(core, &tmp, clr->white, "doublexp");
}

int	draw_pause(t_core *core, int bar_rel)
{
	t_vec2	tmp;
	t_vec2	center;

	center = vec2t(core->mlx.width / 2, core->mlx.height / 2);
	draw_bkg_pause(core, bar_rel);
	if (!bar_rel)
	{
		playsound("pause_open", 0, 1, 0);
		tmp = vec2t(center.x - 30, center.y - 20);
		r_drawtext(core, &tmp, 0xFFFFFF, "Pause Menu");
		tmp.x = center.x - 78;
		r_drawtext(core, &tmp, 0xFFFFFF, "< u > to show all commands");
		tmp.x = center.x - 66;
		r_drawtext(core, &tmp, 0xFFFFFF, "< i > to write a command");
		tmp.x = center.x - 78;
		r_drawtext(core, &tmp, 0xFFFFFF, "< ESC > to force quit game");
		tmp.x = center.x - 60;
		r_drawtext(core, &tmp, 0xFFFFFF, "< space > to unpause");
	}
	tmp = vec2t(center.x - 108, center.y + 80);
	if (get_game(core)->cmd.is_open)
		r_drawtext(core, &tmp, 0xFFFFFF, get_game(core)->cmd.buffer);
	return (1);
}
