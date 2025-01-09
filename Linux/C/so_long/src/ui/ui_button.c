/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:01:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/14 04:03:18 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	button_click(int k, t_vec2 p, t_core *c, t_uibutton *b)
{
	t_uibutton	btn;
	int			i;

	if (k != m_left_click || !get_submenu(c)->defined)
		return (0);
	i = 0;
	while (i < 5)
	{
		btn = get_submenu(c)->button[i];
		if (btn.defined)
		{
			if (p.x >= btn.ui.x && p.x <= (btn.ui.x + btn.ui.w)
				&& p.y >= btn.ui.y && p.y <= (btn.ui.y + btn.ui.h))
			{
				sl_memcpy(b, &btn, sizeof(t_uibutton));
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	ui_play_button(t_core *core)
{
	playsound("play_button", 1, 1, 0);
	set_map_origin(core);
	set_status(core, status_playing);
	mlx_clear_window(get_mlx(core)->ptr, get_mlx(core)->win);
	playsound("dungeon_quest", 0, 1, 0);
}

void	ui_resume_button(t_core *core)
{
	playsound("pause_close", 0, 0, 0);
	mlx_clear_window(get_mlx(core)->ptr, get_mlx(core)->win);
	set_status(core, status_playing);
	playsound("dungeon_quest", 0, 1, 0);
	set_key_status(core, 1);
}
