/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_client_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:26:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:37:23 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

double	scr_get_movespeed(void)
{
	t_dvars		*dvar;
	t_key		*key;
	t_key		*key2;

	dvar = dvar_findvar("g_speed");
	if (dvar)
	{
		key = get_key(BUTTON_SPRINT);
		key2 = get_key(BUTTON_MOVE_FORWARD);
		if (key && key2 && key->is_pressed && key2->is_pressed)
			return (dvar->dvalue * 2.0f);
		else
			return (dvar->dvalue);
	}
	return (0.05f);
}

void	scr_move_forward(void)
{
	t_player	*p;
	t_vec2		v;

	p = get_user();
	if (p && p->status == USER_ALIVE)
	{
		p->speed = scr_get_movespeed();
		v = (t_vec2){(int)(p->origin.x + ((p->dir.x * 2) * p->speed)),
			(int)(p->origin.y)};
		if (bg_can_walk(v))
			p->origin.x += p->dir.x * p->speed;
		v = (t_vec2){(int)(p->origin.x),
			(int)(p->origin.y + ((p->dir.y * 2) * p->speed))};
		if (bg_can_walk(v))
			p->origin.y += p->dir.y * p->speed;
	}
}

void	scr_move_backward(void)
{
	t_player	*p;
	t_vec2		v;

	p = get_user();
	if (p && p->status == USER_ALIVE)
	{
		p->speed = scr_get_movespeed();
		v = (t_vec2){(int)(p->origin.x - ((p->dir.x * 2) * p->speed)),
			(int)(p->origin.y)};
		if (bg_can_walk(v))
			p->origin.x -= p->dir.x * p->speed;
		v = (t_vec2){(int)(p->origin.x),
			(int)(p->origin.y - ((p->dir.y * 2) * p->speed))};
		if (bg_can_walk(v))
			p->origin.y -= p->dir.y * p->speed;
	}
}

void	scr_move_right(void)
{
	t_player	*p;
	t_vec2		v;

	p = get_user();
	if (p && p->status == USER_ALIVE)
	{
		p->speed = scr_get_movespeed();
		v = (t_vec2){(int)(p->origin.x - ((p->dir.y * 2) * p->speed)),
			(int)(p->origin.y)};
		if (bg_can_walk(v))
			p->origin.x -= p->dir.y * p->speed;
		v = (t_vec2){(int)(p->origin.x),
			(int)(p->origin.y + ((p->dir.x * 2) * p->speed))};
		if (bg_can_walk(v))
			p->origin.y += p->dir.x * p->speed;
	}
}

void	scr_move_left(void)
{
	t_player	*p;
	t_vec2		v;

	p = get_user();
	if (p && p->status == USER_ALIVE)
	{
		p->speed = scr_get_movespeed();
		v = (t_vec2){(int)(p->origin.x + ((p->dir.y * 2) * p->speed)),
			(int)(p->origin.y)};
		if (bg_can_walk(v))
			p->origin.x += p->dir.y * p->speed;
		v = (t_vec2){(int)(p->origin.x),
			(int)(p->origin.y - ((p->dir.x * 2) * p->speed))};
		if (bg_can_walk(v))
			p->origin.y -= p->dir.x * p->speed;
	}
}
