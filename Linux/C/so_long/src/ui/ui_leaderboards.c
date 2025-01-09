/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_leaderboards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 06:17:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/02 15:24:10 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	leaderboard_free(t_core *core)
{
	if (get_client(core)->lead_buff)
	{
		free(get_client(core)->lead_buff);
		get_client(core)->lead_buff = NULL;
	}
}

static void	leaderboard_info(t_core *core, t_vec2 *ori)
{
	t_client	*cli;
	int			i;
	int			tmp;
	void		*ptr;
	int			val;

	ptr = get_account(core);
	cli = get_client(core);
	r_drawtext(core, ori, 0xFFFFFF, "Remaining XP     : ");
	r_drawtext(core, ori, 0xFFFFFF, "Level            : ");
	r_drawtext(core, ori, 0xFFFFFF, "Total Collected  : ");
	r_drawtext(core, ori, 0xFFFFFF, "Total Killed     : ");
	r_drawtext(core, ori, 0xFFFFFF, "Total Steps      : ");
	tmp = ori->x;
	ori->y = 53;
	i = 0;
	while (!core->game.stop_proc && i < 5)
	{
		val = *(int *)(ptr + (i * sizeof(int)));
		cli->lead_buff = sl_itoa(val);
		ori->x = tmp + 192 - r_textwidth(cli->lead_buff);
		r_drawtext(core, ori, 0xFFFFFF, cli->lead_buff);
		leaderboard_free(core);
		i++;
	}
}

void	show_leaderboard(t_core *core)
{
	t_vec2		title;

	playsound("popup", 0, 0, 0);
	leaderboard_free(core);
	title = vec2t(115 + (r_textwidth("Leaderboards :") / 2), 33);
	print_img(core, vec2t(115, 20), "/ui_leaderboard");
	r_drawtext(core, &title, 0xFFFFFFFF, "Leaderboards :");
	title = vec2t(118, 53);
	leaderboard_info(core, &title);
}
