/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_client_look.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:26:46 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:37:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

void	scr_look_up(void)
{
	t_player	*p;

	p = get_user();
	if (p && p->vangle < 0.7 && p->status == USER_ALIVE)
	{
		p->vangle += 0.1;
		if (p->vangle >= 0.7)
			p->vangle = 0.7;
	}
}

void	scr_look_down(void)
{
	t_player	*p;

	p = get_user();
	if (p && p->vangle > -0.7 && p->status == USER_ALIVE)
	{
		p->vangle -= 0.1;
		if (p->vangle < -0.7)
			p->vangle = -0.7;
	}
}

void	scr_look_left(void)
{
	t_player	*p;
	double		odir;
	double		oplane;

	p = get_user();
	if (p && p->status == USER_ALIVE)
	{
		odir = p->dir.x;
		p->dir.x = p->dir.x * cosf(-0.1) - p->dir.y * sinf(-0.1);
		p->dir.y = odir * sinf(-0.1) + p->dir.y * cosf(-0.1);
		oplane = p->plane.x;
		p->plane.x = p->plane.x * cosf(-0.1) - p->plane.y * sinf(-0.1);
		p->plane.y = oplane * sinf(-0.1) + p->plane.y * cosf(-0.1);
	}
}

void	scr_look_right(void)
{
	t_player	*p;
	double		odir;
	double		oplane;

	p = get_user();
	if (p && p->status == USER_ALIVE)
	{
		odir = p->dir.x;
		p->dir.x = p->dir.x * cosf(0.1) - p->dir.y * sinf(0.1);
		p->dir.y = odir * sinf(0.1) + p->dir.y * cosf(0.1);
		oplane = p->plane.x;
		p->plane.x = p->plane.x * cosf(0.1) - p->plane.y * sinf(0.1);
		p->plane.y = oplane * sinf(0.1) + p->plane.y * cosf(0.1);
	}
}
