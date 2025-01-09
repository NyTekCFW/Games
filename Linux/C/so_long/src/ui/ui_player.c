/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:42:41 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/07 14:38:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	dodamage(t_core *core, int damage, int type)
{
	t_client	*client;
	t_vec2		center;
	t_vec2		tmp;

	client = get_client(core);
	client->health -= damage;
	if (client->health <= 0)
	{
		client->health = 0;
		client->display = 0;
		set_status(core, status_dead);
		center = vec2t(core->mlx.width / 2, core->mlx.height / 2);
		tmp = vec2t(center.x - (r_textwidth("GAME OVER") / 2), center.y);
		r_drawtext(core, &tmp, 0xFFFFFF, "GAME OVER");
		if (flag_status(core, p_info))
			show_info(core);
	}
	else if (type == g_fire)
		playsound("link_burned", 0, 0, 1);
	else if (type == g_axis)
		playsound("link_hurt", 0, 0, 1);
}

void	death_player(t_core *core)
{
	clock_t	i;

	if (get_status(core) == status_dead)
	{
		playsound("game_over", 0, 1, 0);
		i = clock() + (CLOCKS_PER_SEC * 14);
		while (clock() < i)
			;
		win_exit(core);
	}
}
