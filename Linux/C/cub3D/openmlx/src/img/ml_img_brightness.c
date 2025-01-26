/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_brightness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:38:50 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:35:51 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	_brightness(t_shaders *sh, float t, __uint32_t r)
{
	__uint32_t	i;
	__uint32_t	b;
	__uint32_t	n;
	void		*adr;

	i = 0;
	if (!sh)
		return ;
	adr = (void *)sh->img.addr;
	n = sh->img.size;
	while (i + sizeof(int) <= n)
	{
		b = *(__uint32_t *)(adr + i);
		if (is_valid_color(b))
			*(__uint32_t *)(adr + i) = blend_colors(b, r, t);
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

	if ((int)roundf(i * (1 << 8)) == (int)roundf(0.5f * (1 << 8)))
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
