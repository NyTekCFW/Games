/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_text.h                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 15:09:27 by NyTekCFW                                 */
/*   Updated: 20/12/2024 15:12:44 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREGFX_TEXT_H
# define COREGFX_TEXT_H

u8		r_glyph_width(char c);
u8		r_glyph_height(void);
u32		r_textwidth(const char *str);
void	draw_text(char *str, s16 x, s16 y, u16 clr);

#endif