/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:22:25 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:22:25 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_client_move.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/core/parsing.h"
#include "../../includes/bgame/bg_register_trigger.h"
#include "../../includes/game/g_axis.h"

void	execute_keyboard(void)
{
	int	i;

	i = -1;
	while (++i < *get_key_count())
		keynum_execute(i);
}

void	mouse_update(t_ml *lx, t_vec2 u)
{
	static t_vec2	last = (t_vec2){0, 0};
	t_vec2			delta;
	t_vec4f			d;
	t_player		*user;

	user = get_user();
	if (user && user->status == USER_ALIVE && lx)
	{
		delta = (t_vec2){0 - (u.x - last.x), u.y - last.y};
		d = (t_vec4f){0.0001, 0, user->dir.x, user->plane.x};
		d.y = delta.x * d.x;
		user->dir.x
			= user->dir.x * cosf(-d.y) - user->dir.y * sinf(-d.y);
		user->dir.y = d.z * sinf(-d.y) + user->dir.y * cosf(-d.y);
		user->plane.x
			= user->plane.x * cosf(-d.y) - user->plane.y * sinf(-d.y);
		user->plane.y = d.w * sinf(-d.y) + user->plane.y * cosf(-d.y);
		user->vangle -= delta.y * d.x;
		if (user->vangle > 0.7)
			user->vangle = 0.7;
		if (user->vangle < -0.7)
			user->vangle = -0.7;
		last = (t_vec2){lx->width / 2, lx->height / 2};
		lx->refresh = 1;
	}
}

void	mouse_move(int x, int y)
{
	t_menu		*menu;
	t_player	*user;
	t_ml		*lx;

	user = get_user();
	lx = gmlx(ACT_GET);
	menu = dbg_menu(ACT_GET);
	if (lx && !menu->_open && user && user->status == USER_ALIVE)
	{
		mouse_update(lx, (t_vec2){x, y});
		if ((x != lx->width / 2 || y != lx->height / 2)
			&& *(int*)getvar("cg_mouse_fix"))
			mlx_mouse_move(lx->ptr, lx->win,
				lx->width / 2, lx->height / 2);
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
