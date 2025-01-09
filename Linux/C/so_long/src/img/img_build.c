/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:19:16 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/06 23:34:02 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	compile_img(t_imgx *dest, t_imgx *imgx1, t_imgx *imgx2)
{
	__uint32_t	size;
	__uint32_t	i;
	__uint32_t	df;

	i = 0;
	if (!dest || !imgx1 || !imgx2)
		return ;
	size = dest->height * dest->img.len + dest->width * (dest->img.bpp / 8);
	while (i < size)
	{
		df = get_value(imgx2->img.addr + i);
		if (df != 0 && df != 0xFF000000)
			set_value(dest->img.addr + i, df);
		else
			set_value(dest->img.addr + i,
				get_value(imgx1->img.addr + i));
		i += 4;
	}
}

static void	insert_rupee(t_vec4 *gp, void **clr, char **adr, t_imgx *imgx2)
{
	if (gp->x >= 15 && gp->x <= 45 && gp->y >= 15 && gp->y <= 43)
	{
		gp->z++;
		adr[1] = imgx2->img.addr + get_px_adr(&imgx2->img, vec2t(gp->z, gp->w));
		if (get_value(adr[1]) == 0x030303)
			set_value(adr[0], 0);
		if (get_value(adr[1]) != 0xFF000000
			&& get_value(adr[1]) != 0 && get_value(adr[1]) != 0x030303)
		{
			*(__uint32_t *)clr[1]
				= smooth_argb(*(__uint32_t *)clr[1], *(__uint32_t *)clr[0], 1);
			set_value(adr[0], *(__uint32_t *)clr[1]);
		}
		if (gp->z == 30)
			gp->w++;
	}
}

void	rupee_render(t_core *c, t_imgx *d, t_imgx *i1, t_imgx *i2)
{
	void	*clr[2];
	char	*adr[2];
	t_vec4	gp;
	t_game	*gm;

	gm = get_game(c);
	gp = vec4t(0, 0, 0, 0);
	clr[0] = get_color(c)->ptr;
	clr[1] = &get_color(c)->rgb;
	while (!gm->stop_proc && gp.y < i1->height)
	{
		gp.z = -1;
		gp.x = 0;
		while (!gm->stop_proc && gp.x < i1->width)
		{
			adr[0] = d->img.addr + get_px_adr(&d->img, vec2t(gp.x, gp.y));
			adr[1]
				= i1->img.addr + get_px_adr(&i1->img, vec2t(gp.x, gp.y));
			set_value(adr[0], get_value(adr[1]));
			insert_rupee(&gp, clr, adr, i2);
			gp.x++;
		}
		gp.y++;
	}
}
