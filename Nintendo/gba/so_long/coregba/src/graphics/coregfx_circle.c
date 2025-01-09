/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_circle.c                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 17/12/2024 20:40:06 by NyTekCFW                                 */
/*   Updated: 17/12/2024 20:48:00 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static void	draw_circle_line(u16 *vbuf, int y, int x1, int x2, int h, int w, int wo, u16 color)
{
	int			sx = 0;
	int			ex = 0;
	u32			size = 0;

	if (y < 0 || y >= h)
		return ;
	sx = max(0, x1);
	ex = min(w - 1, x2);
	if (sx > ex)
		return ;
	size = (ex - sx + 1) * sizeof(u16);
	size = (size + 3) & ~3;
	CpuFill(&vbuf[y * wo + sx], color, (ex - sx + 1) * sizeof(u16));
}

IN_IWRAM void	draw_circle(u16 x, u16 y, u16 rad, u16 clr, u8 fill)
{
	u16			*vbuf = gcm_get_draw_buffer();
	t_virtual	*vmem = get_virtual();
	u16			w = vmem->scaled_width;
	u16			h = vmem->scaled_height;
	u16			wo = vmem->width;
	s16			dx = 0;
	s16			dy = rad;
	s16			d = 3 - (2 * rad);

	if (rad < 3)
		return ;
	while (dy >= dx)
	{
		if (fill)
		{
			draw_circle_line(vbuf, y + dy, x - dx, x + dx, h, w, wo, clr);
			draw_circle_line(vbuf, y - dy, x - dx, x + dx, h, w, wo, clr);
			draw_circle_line(vbuf, y + dx, x - dy, x + dy, h, w, wo, clr);
			draw_circle_line(vbuf, y - dx, x - dy, x + dy, h, w, wo, clr);
		}
		else
		{
			mx_put_pixel(vmem, vbuf, x + dx, y + dy, clr);
			mx_put_pixel(vmem, vbuf, x - dx, y + dy, clr);
			mx_put_pixel(vmem, vbuf, x + dx, y - dy, clr);
			mx_put_pixel(vmem, vbuf, x - dx, y - dy, clr);
			mx_put_pixel(vmem, vbuf, x + dy, y + dx, clr);
			mx_put_pixel(vmem, vbuf, x - dy, y + dx, clr);
			mx_put_pixel(vmem, vbuf, x + dy, y - dx, clr);
			mx_put_pixel(vmem, vbuf, x - dy, y - dx, clr);
		}
		if (d <= 0)
			d += 4 * dx + 6;
		else
		{
			d += 4 * (dx - dy) + 10;
			--dy;
		}
		++dx;
	}
}
