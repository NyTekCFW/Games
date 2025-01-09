/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   print_submenu.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 02:13:50 by NyTekCFW                                 */
/*   Updated: 27/12/2024 20:15:53 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	print_minimap_menu(void)
{
	
}

void	print_fps(void)
{
	static u16	min_x = 0xFFFF;
	static u16	n_w = 0;
	t_virtual	*virtual = get_virtual();
	t_engine	*engine = get_engine();
	char		*t = xitoa(engine->fps_out);
	u16			w = 0;
	u16			sw = 0;

	if (t)
	{
		w = (u16)r_textwidth(t);
		sw = virtual->scaled_width - w;
		if (sw < min_x)
		{
			min_x = sw;
			n_w = (virtual->scaled_width - 1) - min_x;
		}
		draw_rectangle(min_x, 1, n_w, 9, 0x3def, 1);
		draw_text(t, sw, 1, 0x7C7F);
		xfree((void **)&t);
	}
}
