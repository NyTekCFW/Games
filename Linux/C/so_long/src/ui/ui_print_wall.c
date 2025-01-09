/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_print_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:51:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/21 05:37:20 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	printwallx(t_core *core, t_vec2 xy, t_vec2 num, t_vec2 max)
{
	t_vec2	zones;

	zones = get_client(core)->zones;
	if (!num.x && !zones.x && num.y < max.y
		&& ((num.y > 0) || (num.y >= 0 && zones.y > 0)))
		print_img(core, xy, "/wall_left");
	else if (num.x == max.x && num.y < max.y && ((num.y > 0)
			|| (num.y >= 0 && zones.y > 0)))
		print_img(core, xy, "/wall_right");
	else if ((num.x >= 1 && num.x < max.x && num.y == max.y) || (((num.x > 0)
				|| (num.x >= 0 && zones.x > 0))
			&& num.x < max.x && num.y == max.y && (zones.x > 0
				|| zones.y > 0)))
		print_img(core, xy, "/wall_down");
	else if ((num.x >= 1 && num.x < max.x && !num.y && !zones.y)
		|| (!num.x && !num.y && !zones.y && zones.x > 0))
		print_img(core, xy, "/wall_up");
	else if ((!num.x && !num.y && !zones.y && !zones.x)
		|| (!num.x && num.y == max.y)
		|| (num.x == max.x && num.y == max.y)
		|| (num.x == max.x && !num.y))
		return ;
	else
		print_img(core, xy, "/wall_rock");
}
