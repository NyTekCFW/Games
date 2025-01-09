/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_text.c                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 17/12/2024 23:11:36 by NyTekCFW                                 */
/*   Updated: 17/12/2024 23:11:38 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

u8	r_glyph_width(char c)
{
	if (c >= 0x20 && c <= 0x7E)
		return (font_basic_width[c - 0x20]);
	if (c >= 0x0B && c <= 0x1D)
		return (font_button_width[c - 0x0B]);
	return (8);
}

u8	r_glyph_height(void)
{
	return (9);
}

u32	r_textwidth(const char *str)
{
	u32	width = 0;

	if (!str)
		return (0);
	while (*str)
	{
		width += r_glyph_width(*str);
		++str;
	}
	return (width);
}

static void	draw_symbol(char c, s16 x, s16 y, u8 space)
{
	char	beg = 0x0B;
	char	*str = "buttons_8x8";

	switch (c)
	{
		case 0x14:case 0x15:str = "buttons_16x8"; beg = 0x14; break;
		case 0x16:case 0x17:str = "buttons_24x8"; beg = 0x16; break;
		case 0x18:case 0x19:str = "buttons_check_8x8"; beg = 0x18; break;
		case 0x1A:case 0x1B:case 0x1C:case 0x1D:str = "buttons_trophy_8x8"; beg = 0x1A; break;
	}
	draw_sprite(x, y, c - beg, str);
}

IN_IWRAM void	draw_text(char *str, s16 x, s16 y, u16 clr)
{
	t_virtual	*vmem = get_virtual();
	u16			*vbuf = gcm_get_draw_buffer();
	int			x_new = x;
	char		*c = 0;
	s16			i = 0;
	s8			x2 = 0;
	s8			y2 = 0;
	u8			space = 0;

	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			y += 9;
			x = x_new;
			++i;
			continue ;
		}
		space = r_glyph_width(str[i]);
		if (str[i] >= 0x0B && str[i] <= 0x1D)
			draw_symbol(str[i], x, y, space);
		else if (str[i] >= 0x20 && str[i] <= 0x7E)
		{
			if (x >= 0 && x + space <= vmem->scaled_width
				&& y >= 0 && y + 9 <= vmem->scaled_height)
			{
				c = font_basic[(u8)str[i] - 0x20];
				y2 = -1;
				while (++y2 < 8)
				{
					if (c[y2])
					{
						x2 = 8;
						while (--x2 >= 0)
						{
							if (c[y2] & (1 << x2))
								vbuf[(y + y2) * vmem->width + (x + x2)] = clr;
						}
					}
				}
			}
		}
		x += space;
		++i;
	}
}
