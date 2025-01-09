/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 06:17:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/01 09:36:37 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	info_free(t_core *core)
{
	if (get_client(core)->info_buff)
	{
		free(get_client(core)->info_buff);
		get_client(core)->info_buff = NULL;
	}
}

static void	info_info(t_core *core, t_vec2 *ori)
{
	t_client	*cli;
	int			i;
	int			tmp;
	clock_t		val[3];

	cli = get_client(core);
	val[0] = cli->step;
	val[1] = get_anim(core)->frame[f_fps];
	val[2] = cli->health;
	r_drawtext(core, ori, 0xFFFFFF, "Step's :           ");
	r_drawtext(core, ori, 0xFFFFFF, "FPS    :           ");
	r_drawtext(core, ori, 0xFFFFFF, "Health :           ");
	tmp = ori->x;
	ori->y = 33;
	i = 0;
	while (!core->game.stop_proc && i < 3)
	{
		cli->info_buff = sl_itoa(val[i]);
		ori->x = tmp + 112 - r_textwidth(cli->info_buff);
		r_drawtext(core, ori, 0xFFFFFF, cli->info_buff);
		info_free(core);
		i++;
	}
}

void	show_info(t_core *core)
{
	t_vec2		title;
	int			x;

	x = get_mlx(core)->width;
	info_free(core);
	title = vec2t(x - 114 + (r_textwidth("Information :") / 4), 16);
	print_img(core, vec2t(x - 117, 3), "/ui_info");
	r_drawtext(core, &title, 0xFFFFFFFF, "Information :");
	title = vec2t(x - 114, 33);
	info_info(core, &title);
}
