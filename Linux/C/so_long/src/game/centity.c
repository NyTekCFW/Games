/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 06:19:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/07 15:16:20 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_vec2	get_ent_pos(t_core *core, t_ui ui)
{
	t_vec2	xy;
	t_vec4	mi;

	mi = get_game(core)->map_i;
	xy = vec2t(mi.x - ui.x, mi.y - ui.y);
	if (xy.x < 0)
		xy.x *= -1;
	if (xy.y < 0)
		xy.y *= -1;
	xy = vec2t(xy.x / 60, xy.y / 60);
	return (xy);
}

int	get_player_presence(t_core *core, t_vec4 mi, t_vec2 xy)
{
	t_vec2	origin;
	t_vec4	sq;
	t_game	*gm;

	gm = get_game(core);
	origin = get_client(core)->origin;
	sq.x = (gm->map_rng.x * 60) + origin.x + 20;
	sq.y = (gm->map_rng.y * 60) + origin.y + 20;
	sq.z = mi.x + ((xy.x * 60) + 30);
	sq.w = mi.y + ((xy.y * 60) + 30);
	if (sq.x - 20 <= sq.z + 29 && sq.x + 20 >= sq.z - 29
		&& sq.y - 20 <= sq.w + 29 && sq.y + 20 >= sq.w - 29)
		return (1);
	return (0);
}
