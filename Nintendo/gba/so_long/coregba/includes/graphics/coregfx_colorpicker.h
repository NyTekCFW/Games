/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_colorpicker.h                                                    */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:09:37 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREGFX_COLORPICKER_H
# define COREGFX_COLORPICKER_H

typedef struct colorpicker_s
{
	s8		row;
	s8		column;
	u8		is_open;
	u16		p_x;
	u16		p_y;
	void	(*callback)(u8, u8, u16);
}ALIGNED(4)	t_cp;

void	show_color_picker(void);
void	open_color_picker(void);
void	close_color_picker(void);
#endif