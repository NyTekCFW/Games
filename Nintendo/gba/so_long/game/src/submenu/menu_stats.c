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

static const char	**_get_data(void)
{
	static const char	*_stats_data[STATS_LD_MAX] = {NULL};

	return (_stats_data);
}

static void	_init_data(void)
{
	const char	**data = _get_data();
	int	i = 0;

	while (i < STATS_LD_MAX)
	{
		data[i] = get_stat_info(i);
		++i;	
	}
}

static void	_clear_data(void)
{
	const char	**data = _get_data();
	int	i = 0;

	while (i < STATS_LD_MAX)
	{
		data[i] = _get_data()[i];
		xfree((void **)&data[i]);
		data[i] = NULL;
		++i;	
	}
	submenu_back();
}

static void	_print_stats_elem(void)
{
	s8			i = 0;
	int			index = 0;
	t_stats		*stat = get_stats();
	t_submenu	*menu = get_submenu();
	const char	**buffer = _get_data();

	while (i < 7)
	{
		index = get_scroll_in_list(1, menu->current_scroll, i, 7, 6);
		draw_text(buffer[index], 2, 2 + (i * 10), 0xFFFF);
		if (index == menu->current_scroll)
			draw_rectangle(0, (i * 10), 120, 11, 0xFFFF, 0);
		++i;
	}
}

static void	_draw_stats(void)
{
	draw_rectangle(2, 2, 92, 68, 0x3def, 1);
	_print_stats_elem();
}

static void	_increment_scroll(void)
{
	submenu_scroll_increment(7, NULL);
	_draw_stats();
}

static void	_decrement_scroll(void)
{
	submenu_scroll_decrement(7, NULL);
	_draw_stats();
}

void	submenu_stats(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_B, _clear_data);
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	draw_text(STR_BUTTON_B " Back| " STR_DPAD_UP_DOWN " Move", 2, 71, 0xFFFF);
	_init_data();
	_print_stats_elem();
}
