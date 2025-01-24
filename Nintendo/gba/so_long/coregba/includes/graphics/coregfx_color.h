/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_color.h                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:09:27 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREGFX_COLOR_H
# define COREGFX_COLOR_H

void	replace_color(u16 index, u16 color);
void	rgb15_to_rgb(u16 rgb15, u8 *r, u8 *g, u8 *b);
void	set_palette(const u16 *pal, u16 size, void (*callback)(u16 *));
u16	    *get_palette(void);
u16		(*get_stab_color(void))[16];
u16		rgb_to_15bit(u8 r, u8 g, u8 b);
u16		get_color_at(u16 index);
u16		get_color_index(u16 color);

#endif