/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_color_picker_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 03:36:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:15:51 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static int	_min(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	_cpicker_check_cursor(t_colpicker *p, t_vec2 v, t_vec2 u)
{
	if (is_in_range((t_vec2){v.x + 258, v.y + 5}, u, (t_vec2){10, 10}))
	{
		p->is_open = 0;
		if (p->c_color)
			*p->c_color = p->init_color;
		p->c_color = NULL;
	}
}

void	cpicker_check_cursor(t_ml *lx, t_vec2 u)
{
	t_colpicker	*p;
	t_vec2		v;

	p = &lx->cpicker;
	v = p->u;
	if (is_in_range((t_vec2){v.x + 12, v.y + 21}, u, p->grd))
		p->cursor = (t_vec2){_min((u.x - v.x) - 15, 0),
			_min((u.y - v.y) - 22, 0)};
	else if (is_in_range((t_vec2){v.x + 10, v.y + 280}, u, p->bar))
		p->cursor_bar.x = _min((u.x - v.x) - 15, 0);
	else if (is_in_range((t_vec2){v.x + 240, v.y + 5}, u, (t_vec2){10, 10}))
	{
		p->is_open = 0;
		*p->c_color = p->new_color;
		p->c_color = NULL;
	}
	_cpicker_check_cursor(p, v, u);
}

static void	_gradient(t_vec2 u, float *d, __uint32_t b[], t_shaders *sh)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		u.x = -1;
		while (++u.x < sh->img.width)
		{
			*d = (float)u.x / (sh->img.width - 1);
			if (*d <= 0)
				*d = 0.01;
			b[2] = gradient(b[0], b[1], *d);
			if (!is_valid_color(b[2]))
				b[2] = 0x030303;
			if (lx->cpicker.cursor.x == u.x && lx->cpicker.cursor.y == u.y)
				lx->cpicker.new_color = b[2];
			set_color(&sh->img, get_px_adr(&sh->img, u), b[2]);
		}
		*d = ((float)u.y / (sh->img.height - 1)) / 56;
		if (*d <= 0)
			*d = 0.01;
	}
}

void	cpicker_grad(t_ml *lx)
{
	__uint32_t	b[3];
	t_shaders	*sh;
	t_vec2		u;
	float		d;

	if (lx)
	{
		sh = get_img("cpiker_gradient");
		if (sh)
		{
			d = 0.1f;
			fill_img_color(&sh->img, 0);
			b[1] = lx->cpicker.bar_color;
			while (b[1] > 0xFFFFFF)
				b[1] /= 10;
			xmemcpy(b, (__uint32_t []){0xFFFFFF, b[1], 0}, sizeof(b));
			u = (t_vec2){-1, -1};
			while (++u.y < sh->img.height)
			{
				_gradient(u, &d, b, sh);
				b[0] = _min(gradient(b[0], 0, d), 0x030303);
				b[1] = gradient(b[1], 0, d);
			}
		}
	}
}
