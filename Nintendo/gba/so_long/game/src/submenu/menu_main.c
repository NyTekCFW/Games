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
	play_sfx("snd_popup");
	submenu_access(get_submenu()->current_scroll + 1);
}
/*
static void	_spoof_button(u8 prev)
{
	t_submenu	*sub = get_submenu();
	u8			u = (sub->current_scroll > 0) ? 2 : 0;

	draw_rectangle(2, 2 + (prev * 8) + u, 8, 8, 0x3def, 1);
	draw_sprite(2, 2 + (sub->current_scroll * 8) + u, 0, "buttons_8x8");
}
*/
static void	_draw_main(void)
{
	const char	*text[8] = {"Play", "Skin Color", "Custom Maps", "Options", "Controls", "Trophies", "Stats", "Reset Stats"};
	u8			i = 0;
	u8			u = 0;
	s8			scroll = get_submenu()->current_scroll;

	draw_rectangle(2, 2, 94, 68, 0x3def, 1);
	draw_sprite(2, 2 + (scroll * 8), 0, "buttons_8x8");
	while(i < 8)
	{
		u = (i > 0) ? 1 : 0;
		draw_text(text[i], (scroll == i) ? 11 : 2, 2 + (i * 8), 0xFFFF);
		++i;
	}
}

static void	_decrement_scroll(void)
{
	u8	prev = 0;

	submenu_scroll_decrement(7, &prev);
	_draw_main();
}

static void	_increment_scroll(void)
{
	u8	prev = 0;

	submenu_scroll_increment(7, &prev);
	_draw_main();
}

void	submenu_main_menu(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_A, _select);
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	draw_sprite(104, 63, 0, "link_walk");
	_draw_main();
	draw_text(STR_BUTTON_A " Select| " STR_DPAD_UP_DOWN " Move", 2, 71, 0xFFFF);
}
