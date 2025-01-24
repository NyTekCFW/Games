/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_options.c                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 28/12/2024 01:00:46 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:14:59 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	_opposite(void)
{
	t_submenu	*sub = get_submenu();
	t_engine	*engine = get_engine();
	t_settings	*s = get_settings();

	switch (sub->current_scroll)
	{
		case VAR_SHOW_FPS:
		{
			s->vars[VAR_SHOW_FPS] = !s->vars[VAR_SHOW_FPS];
			break;
		}
		case VAR_LIMIT_FPS:
		{
			s->vars[VAR_LIMIT_FPS] = !s->vars[VAR_LIMIT_FPS];
			engine->max_fps = (s->vars[VAR_LIMIT_FPS]) ? engine->backup_fps : 255;
			break;
		}
	}
	submenu_refresh();
}

static void	_increment_scroll(void)
{
	submenu_scroll_increment(1, NULL);
	submenu_refresh();
}

static void	_decrement_scroll(void)
{
	submenu_scroll_decrement(1, NULL);
	submenu_refresh();
}

void	draw_options(void)
{
	t_settings	*s = get_settings();
	char		buffer[20] = {0};
	u8			i = 0;

	while (i < 2)
	{
		draw_text(get_dvars_name(buffer, i), 10, 2 + (i * 9), 0xFFFF);
		if (i == get_submenu()->current_scroll)
			draw_sprite(2, 2 + (i * 9), 0, "buttons_8x8");
		++i;
	}
}

void	submenu_options(void)
{
	keynum_release(BUTTON_A);
	unbind_allkeys();
	keynum_replace(BUTTON_A, _opposite);
	keynum_replace(BUTTON_B, submenu_back);
	keynum_replace(BUTTON_MOVE_FORWARD, _decrement_scroll);
	keynum_replace(BUTTON_MOVE_BACKWARD, _increment_scroll);
	draw_options();
	draw_text(STR_BUTTON_B " Back| " STR_DPAD_UP_DOWN " Move", 2, 71, 0xFFFF);
}
