/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_colorpicker.c                                                    */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 28/12/2024 16:32:33 by NyTekCFW                                 */
/*   Updated: 28/12/2024 19:25:02 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static void	_previous_color(void)
{
	t_cp	*cp = get_color_picker();
	s8		row = cp->row;

	cp->row = (row - 1 < 0) ? 12 : row - 1;
	cp->column = 8;
	show_color_picker();
}

static void	_next_color(void)
{
	t_cp	*cp = get_color_picker();

	cp->row = (cp->row + 1) % 13;
	cp->column = 8;
	show_color_picker();
}

static void	_increase_brightness(void)
{
	t_cp	*cp = get_color_picker();

	cp->column = min(cp->column + 1, 15);
	show_color_picker();
}

static void	_decrease_brightness(void)
{
	t_cp	*cp = get_color_picker();

	cp->column = max(cp->column - 1, 0);
	show_color_picker();
}

void	open_color_picker(void)
{
	t_cp	*cp = get_color_picker();

	unbind_allkeys();
	cp->row = 0;
	cp->column = 8;
	cp->is_open = 1;
	keynum_replace(BUTTON_MOVE_FORWARD, _increase_brightness);
	keynum_replace(BUTTON_MOVE_BACKWARD, _decrease_brightness);
	keynum_replace(BUTTON_MOVE_RIGHT, _next_color);
	keynum_replace(BUTTON_MOVE_LEFT, _previous_color);
	show_color_picker();
}

void	close_color_picker(void)
{
	t_cp	*cp = get_color_picker();

	unbind_allkeys();
	cp->is_open = 0;
	cp->row = 0;
	cp->column = 8;
}

IN_IWRAM void	show_color_picker(void)
{
	t_cp *cp = get_color_picker();
	u16 (*tab)[16] = get_stab_color();
	s8 c_row = cp->row;
	s8 c_column = cp->column;
	s8 i = 0;
	s8 row = c_row - 1;
	u16 n_x = cp->p_x;

	set_palette(pal_color_picker);
	print_img(cp->p_x, cp->p_y, 26, 26, 0, img_color_picker_bkg);
	while (i < 3)
	{
		switch (i)
		{
			case 0: row = (c_row - 1 < 0) ? 12 : c_row - 1; break;
			case 1: row = c_row; break;
			case 2: row = (c_row + 1) % 13; break;
		}
		draw_rectangle(n_x + 3, cp->p_y + 11, 4, 4, tab[row][(row == c_row) ? c_column : 8], 1);
		if (row == c_row)
		{
			if ((c_column + 1) < 16)
			{
				draw_rectangle(n_x + 2, cp->p_y + 2, 6, 6, 0, 0);
				draw_rectangle(n_x + 3, cp->p_y + 3, 4, 4, tab[row][c_column + 1], 1);
			}
			if ((c_column - 1) > -1)
			{
				draw_rectangle(n_x + 2, cp->p_y + 18, 6, 6, 0, 1);
				draw_rectangle(n_x + 3, cp->p_y + 19, 4, 4, tab[row][c_column - 1], 1);
			}
		}
		++i;
		n_x += 8;
	}
	if (cp->callback)
		cp->callback(cp->row, cp->column, tab[c_row][c_column]);
}
