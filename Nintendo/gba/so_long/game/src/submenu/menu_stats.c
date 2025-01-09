/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_stats.c                                                             */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 21:03:08 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:15:32 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_increment_scroll(void)
{
	submenu_scroll_increment(6, NULL);
	submenu_refresh();
}

static void	_decrement_scroll(void)
{
	submenu_scroll_decrement(6, NULL);
	submenu_refresh();
}

static void	_print_stats_elem(void)
{
	s8			i = 0;
	int			index = 0;
	t_stats		*stat = get_stats();
	t_submenu	*menu = get_submenu();
	char		*buffer = NULL;

	while (i < 7)
	{
		index = get_scroll_in_list(1, menu->current_scroll, i, 6, 6);
		buffer = get_stat_info(index);
		draw_text(buffer, 2, 2 + (i * 10), 0xFFFF);
		if (index == menu->current_scroll)
			draw_rectangle(0, (i * 10), 120, 11, 0xFFFF, 0);
		xfree((void **)&buffer);
		++i;
	}
}

void	submenu_stats(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_B, submenu_back);
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	draw_text(STR_BUTTON_B " Back", 2, 71, 0xFFFF);
	_print_stats_elem();
}
