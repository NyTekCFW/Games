/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:05:09 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/21 00:26:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	colors_init(t_core *core)
{
	get_color(core)->grey = 0x7F7F7F;
	get_color(core)->blue = 0x0000FF;
	get_color(core)->cyan = 0x007FFF;
	get_color(core)->green = 0x00FF00;
	get_color(core)->red = 0xFF0000;
	get_color(core)->black = 0;
	get_color(core)->yellow = 0xFFFF00;
	get_color(core)->purple = 0xFF00FF;
	get_color(core)->white = 0xFFFFFF;
	get_color(core)->brown = 0xD2B48C;
	get_color(core)->rgb = 0xff0000;
	get_color(core)->pos = 0;
	get_color(core)->ptr = get_color(core);
}

static long	smooth_color(long val, long val2, long res, long amount)
{
	if (res < amount)
		amount = 1;
	if (val > val2)
		val -= amount;
	else if (val < val2)
		val += amount;
	if (val < 0)
		val = 0;
	if (val > 0xFF)
		val = 0xFF;
	return (val);
}

__uint32_t	smooth_argb(long value, long new_value, long amount)
{
	__uint32_t	a[2];
	__uint32_t	r[2];
	__uint32_t	g[2];
	__uint32_t	b[2];
	__uint32_t	res[4];

	a[0] = value >> 24;
	r[0] = (value >> 16) & 0xFF;
	g[0] = (value >> 8) & 0xFF;
	b[0] = value & 0xFF;
	a[1] = new_value >> 24;
	r[1] = (new_value >> 16) & 0xFF;
	g[1] = (new_value >> 8) & 0xFF;
	b[1] = new_value & 0xFF;
	res[0] = a[0] - a[1];
	res[1] = r[0] - r[1];
	res[2] = g[0] - g[1];
	res[3] = b[0] - b[1];
	res[0] = smooth_color(a[0], a[1], res[0], amount);
	res[1] = smooth_color(r[0], r[1], res[1], amount);
	res[2] = smooth_color(g[0], g[1], res[2], amount);
	res[3] = smooth_color(b[0], b[1], res[3], amount);
	res[0] = (res[0] << 24) | (res[1] << 16) | (res[2] << 8) | res[3];
	return (res[0]);
}

void	fade_rgb(t_core *core)
{
	__uint32_t	val;
	t_color		*clr;

	clr = get_color(core);
	val = *(__uint32_t *)clr->ptr;
	while (1)
	{
		clr->rgb = val;
		clr->pos++;
		clr->ptr += sizeof(__uint32_t);
		if (clr->pos >= 6)
		{
			clr->ptr = get_color(core);
			clr->pos = 0;
		}
		val = *(__uint32_t *)clr->ptr;
		if (val != 0 || val != 0xFFFFFF)
			break ;
	}
}
