/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_brightness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:38:50 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 05:52:20 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	_brightness(t_shaders *sh, float t, __uint32_t r)
{
	__uint32_t	b;
	__uint32_t	c;
	__uint32_t	i;

	i = 0;
	b = 0;
	while (i < sh->img.size)
	{
		b = get_value(sh->img.addr + b);
		if (is_valid_color(b))
		{
			c = blend_colors(b, r, t);
			set_value(sh->img.addr + b, c);
		}
		i += sizeof(int);
	}
}

/// @brief set a brightness on a img
///0.5f = normal 
/// @param sh image
/// @param i 0 -> 1.0f
void	brightness_img(char *name, float i)
{
	t_shaders	*sh;
	float		t;
	__uint32_t	r;

	if (i == 0.5f)
		return ;
	sh = get_img(name);
	if (sh && i >= 0.0f && i <= 1.0f)
	{
		r = 0;
		t = 0;
		if (i < 0.5f)
		{
			r = 0x030303;
			t = 1.0f - (2.0f * i);
		}
		else if (i > 0.5f)
		{
			r = 0xFFFFFF;
			t = 2.0f * (i - 0.5f);
		}
		_brightness(sh, t, r);
	}
}
