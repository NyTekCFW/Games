/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_rectangle.c                                                      */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 17/12/2024 20:47:49 by NyTekCFW                                 */
/*   Updated: 17/12/2024 20:47:54 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

IN_IWRAM void	draw_rectangle(s16 x, s16 y, s16 w, s16 h, u16 clr, u8 fill)
{
	t_virtual	*vmem = get_virtual();
	u16			*vbuf = gcm_get_draw_buffer();
	u16			*start = NULL;
	s16			j = 0;
	s16			x2 = 0;
	s16			y2 = 0;
	u32			s = 0;

	x2 = max(0, x);
	y2 = max(0, y);
	if (y > vmem->scaled_height || x > vmem->scaled_width || 
		(w = min(w + (x < 0 ? x : 0), vmem->scaled_width - x2)) <= 0 || 
		(h = min(h + (y < 0 ? y : 0), vmem->scaled_height - y2)) <= 0)
		return;
	x = x2;
	y = y2;
	start = &vbuf[(y * vmem->width) + x];
	s = w * sizeof(u16);
	if (fill)
	{
		for (j = 0; j < h; ++j)
		{
			CpuFill(start, clr, s);
			start += vmem->width;
		}
	}
	else
	{
		CpuFill(start, clr, s);
		start += vmem->width * (h - 1);
		CpuFill(start, clr, s);
		start = &vbuf[(y + 1) * vmem->width + x];
		vbuf = start + (w - 1);
		for (j = 1; j < h - 1; ++j)
		{
			*start = clr;
			*vbuf = clr;
			start += vmem->width;
			vbuf += vmem->width;
		}
	}
}
