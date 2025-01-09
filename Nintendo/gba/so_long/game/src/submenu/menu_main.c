/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_main.c                                                              */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 20:15:18 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:14:52 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_select(void)
{
	submenu_access(get_submenu()->current_scroll + 1);
}

static void	_spoof_button(u8 prev)
{
	t_submenu	*sub = get_submenu();

	draw_rectangle(2, 2 + (prev * 9), 8, 8, 0x3def, 1);
	draw_sprite(2, 2 + (sub->current_scroll * 9), 0, "buttons_8x8");
}

static void	_decrement_scroll(void)
{
	u8	prev = 0;

	submenu_scroll_decrement(7, &prev);
	_spoof_button(prev);
}

static void	_increment_scroll(void)
{
	u8	prev = 0;

	submenu_scroll_increment(7, &prev);
	_spoof_button(prev);
}

void	submenu_main_menu(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_A, _select);
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	draw_text("Play\nSkin Color\nCustom Stage\nOptions\nControls\nTrophies\nStats\nReset Stats", 10, 2, 0xFFFF);
	draw_sprite(104, 63, 0, "link_test");
	draw_sprite(2, 2 + (get_submenu()->current_scroll * 9), 0, "buttons_8x8");
}
