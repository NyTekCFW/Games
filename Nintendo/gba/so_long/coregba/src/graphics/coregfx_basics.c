/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_basics.c                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:12:40 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

u16	*get_px_adr(t_virtual* vmem, u16 *vbuf, u16 x, u16 y)
{
	if (y <= vmem->scaled_height && x <= vmem->scaled_width)
		return (&vbuf[y * vmem->width + x]);
	return (NULL);
}

void	mx_put_pixel(t_virtual* vmem, u16 *vbuf, u16 x, u16 y, u16 clr)
{
	if (y <= vmem->scaled_height && x <= vmem->scaled_width)
		vbuf[y * vmem->width + x] = clr;
}

IN_IWRAM void	draw_sprite(s16 x, s16 y, u8 n_image, const char *name)
{
	const u8	*sprite = NULL;
	const u16	*palette = NULL;
	u16			*vbuf = gcm_get_draw_buffer();
	t_virtual	*vmem = get_virtual();
	t_sprites	*sh = get_sprite(name);
	u16			y2 = max(0, y);
	u16			x2 = max(0, x);
	u16			color = 0;
	s16			w2 = 0;
	s16			w3 = 0;
	s16			h2 = 0;
	s16			x3 = x;
	s16			y3 = y;
	s16			map_x_offset = 0;
	u32			i = 0;
	u32			j = 0;

	if (!sh || n_image >= sh->img_count)
		return ;
	set_palette(sh->pal, sh->pal_size, sh->pal_callback);
	palette = ((u16 *)0x05000000);
	w2 = sh->width;
	w3 = w2;
	if (y > vmem->scaled_height || x > vmem->scaled_width || 
		(w3 = min(w3 + (x < 0 ? x : 0), vmem->scaled_width - x2)) <= 0 || 
		(h2 = min(sh->height + (y < 0 ? y : 0), vmem->scaled_height - y2)) <= 0)
		return;
	x = x2;
	y = y2;
	if (x3 < 0)
		map_x_offset = -x3;
	i = (y * vmem->width) + x;
	j = ((y3 < 0 ? -y3 : 0) * w2) + map_x_offset + (n_image * (w2 * sh->height));
	sprite = sh->img + j;
	for (y2 = 0; y2 < h2; ++y2)
	{
		for (x2 = 0; x2 < w3 - 3; x2 += 4)
		{
			y3 = i + x2;
			color = palette[sprite[x2]];
			if (color)
				vbuf[y3] = color;
			color = palette[sprite[x2 + 1]];
			if (color)
				vbuf[y3 + 1] = color;
			color = palette[sprite[x2 + 2]];
			if (color)
				vbuf[y3 + 2] = color;
			color = palette[sprite[x2 + 3]];
			if (color)
				vbuf[y3 + 3] = color;
		}
		while (x2 < w3)
		{
			color = palette[sprite[x2]];
			if (color)
				vbuf[i + x2] = color;
			++x2;
		}
		i += vmem->width;
		sprite += w2;
	}
}

IN_IWRAM void	print_img(s16 x, s16 y, s16 w, s16 h, s8 n_image, const u16 *img)
{
	u16			*vbuf = gcm_get_draw_buffer();
	t_virtual	*vmem = get_virtual();
	u16			*start = NULL;
	u16			*bstart = NULL;
	s16			w2 = w;
	s16			x2 = max(0, x);
	s16			y2 = max(0, y);
	s16			map_y_offset = max(0, -y);
	s16			map_x_offset = max(0, -x);
	u32			offset_image = n_image * (w * h);

	if (!img || y > vmem->scaled_height || x > vmem->scaled_width
		|| (w = min(w + (x < 0 ? x : 0), vmem->scaled_width - x2)) <= 0
		|| (h = min(h + (y < 0 ? y : 0), vmem->scaled_height - y2)) <= 0)
		return;
	start = &vbuf[(y2 * vmem->width) + x2];
	bstart = (u16 *)&img[(map_y_offset * w2) + map_x_offset + offset_image];
	offset_image = ((w * sizeof(u16)) / 4) & 0x1FFFFF;
	x2 = (w * sizeof(u16));
	while (h-- > 0)
	{
		if (!(offset_image % 8))
			CpuFastSet(bstart, start, offset_image);
		else
			CpuCopy16(bstart, start, x2);
		start += vmem->width;
		bstart += w2;
	}
}
