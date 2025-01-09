/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_trophies.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 28/12/2024 00:45:22 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:15:38 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_increment_scroll(void)
{
	submenu_scroll_increment(9, NULL);
	submenu_refresh();
}

static void	_decrement_scroll(void)
{
	submenu_scroll_decrement(9, NULL);
	submenu_refresh();
}

void	draw_trophies_list(void)
{
	s8			i = 0;
	int			index = 0;
	t_submenu	*menu = get_submenu();
	t_trophy	*trophies = get_root()->trophies;

	while (i < 7)
	{
		index = get_scroll_in_list(1, menu->current_scroll, i, 9, 6);
		draw_text(get_trophy_name(index), 2, 2 + (i * 10), 0xFFFF);
		draw_sprite(88, 2 + (i * 10), trophies[index].unlocked * trophies[index].rarity, "buttons_trophy_8x8");
		if (index == menu->current_scroll)
			draw_rectangle(0, (i * 10), 120, 11, 0xFFFF, 0);
		++i;
	}
}

void	submenu_trophies(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_B, submenu_back);
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	draw_trophies_list();
	draw_text(STR_BUTTON_B " Back | " STR_DPAD_UP_DOWN " Move", 2, 71, 0xFFFF);
}
