/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   submenu.c                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 21:50:36 by NyTekCFW                                 */
/*   Updated: 27/12/2024 21:50:37 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_clear_bkg(void)
{
	t_virtual	*virtual = get_virtual();

	gcm_clear_draw_buffer();
	draw_rectangle(0, 0, virtual->scaled_width, virtual->scaled_height, 0xFFFF, 0);
}

void	submenu_set(s8 sub)
{
	t_submenu	*menu = get_submenu();

	if (sub >= 0 && sub < SUB_MAX)
	{
		_clear_bkg();
		menu->prev_count = 0;
		menu->current_scroll = 0;
		menu->current_scroll = sub;
		if (menu->entries[sub])
			menu->entries[sub]();
	}
}

void	submenu_refresh(void)
{
	t_submenu	*menu = get_submenu();

	_clear_bkg();
	if (menu->entries[menu->current_sub])
		menu->entries[menu->current_sub]();
}

s16	get_scroll_in_list(u8 is_list, int scroll, int increment, int size, int display_count)
{
	s16	min = ((display_count / 2) * -1);//-5

	if (is_list)
	{
		if ((scroll + min + increment) < 0)
			return (size + 1 + scroll + min + increment);
		else if ((scroll + min + increment) > size)
			return ((0 + scroll + min + increment) - (size + 1));
		else
			return (scroll + min + increment);
	}
	return (increment);
}

void	submenu_scroll_increment(u8 max, u8 *prev)
{
	t_submenu	*sub = get_submenu();

	if (prev)
		*prev = sub->current_scroll;
	++sub->current_scroll;
	if (sub->current_scroll > max)
		sub->current_scroll = 0;
}

void	submenu_scroll_decrement(u8 max, u8 *prev)
{
	t_submenu	*sub = get_submenu();

	if (prev)
		*prev = sub->current_scroll;
	--sub->current_scroll;
	if (sub->current_scroll < 0)
		sub->current_scroll = max;
}

void	submenu_access(s8 sub)
{
	t_submenu	*menu = get_submenu();

	if (sub >= 0 && sub < SUB_MAX)
	{
		_clear_bkg();
		menu->prev_scroll[menu->prev_count] = menu->current_scroll;
		menu->prev_sub[menu->prev_count] = menu->current_sub;
		menu->current_scroll = 0;
		menu->current_sub = sub;
		++menu->prev_count;
		if (menu->entries[sub])
			menu->entries[sub]();
	}
}

void	submenu_back(void)
{
	t_submenu	*menu = get_submenu();

	if (menu->prev_count > 0)
	{
		_clear_bkg();
		menu->current_scroll = menu->prev_scroll[menu->prev_count - 1];
		menu->current_sub = menu->prev_sub[menu->prev_count - 1];
		--menu->prev_count;
		if (menu->entries[menu->current_sub])
			menu->entries[menu->current_sub]();
	}
}
