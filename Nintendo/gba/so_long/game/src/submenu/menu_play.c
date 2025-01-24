/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_play.c                                                              */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 04/01/2025 03:24:45 by NyTekCFW                                 */
/*   Updated: 04/01/2025 03:24:46 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_map_selection(void)
{
	s8			i = 0;
	int			index = 0;
	t_submenu	*menu = get_submenu();
	char		*buffer = NULL;
	u16			clr = 0xFFFF;

	while (i < 7)
	{
		index = get_scroll_in_list(1, menu->current_scroll, i, 7, 6);
		buffer = get_level_name(index);
		draw_text(buffer, 2, 2 + (i * 10), 0xFFFF);
		if (index == menu->current_scroll)
			draw_rectangle(0, (i * 10), 120, 11, 0xFFFF, 0);
		xfree((void **)&buffer);
		++i;
	}
}

static void	_draw_map_section(void)
{
	draw_rectangle(2, 2, 92, 68, 0x3def, 1);
	_map_selection();
}

static void	_increment_scroll(void)
{
	submenu_scroll_increment(7, NULL);
	_draw_map_section();
}

static void	_decrement_scroll(void)
{
	submenu_scroll_decrement(7, NULL);
	_draw_map_section();
}

void	submenu_play(void)
{
	keynum_release(BUTTON_A);
	unbind_allkeys();
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	keynum_replace(BUTTON_B, submenu_back);
	_map_selection();
	draw_text(STR_BUTTON_B " Back| " STR_DPAD_UP_DOWN " Move", 2, 71, 0xFFFF);
}
