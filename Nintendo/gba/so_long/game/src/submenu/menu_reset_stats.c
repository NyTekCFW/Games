/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_reset_stats.c                                                       */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 28/12/2024 00:48:53 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:15:18 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_reset_yes(void)
{
	t_save		*save = get_save();
	t_stats		*stats = get_stats();
	t_sprites	*sprite = get_sprite("link_test");

	xmemset(stats, 0, sizeof(t_stats));
	save->skin.clr_jacket = 0x030b;
	save->skin.clr_skin = 0x1e7f;
	save->skin.clr_equipment = 0x0178;
	if (sprite)
	{
		sprite->pal[1] = 0x030b;
		sprite->pal[2] = 0x1e7f;
		sprite->pal[3] = 0x0178;
	}
	keynum_release(BUTTON_A);
	submenu_back();
}

void	submenu_reset_stats(void)
{
	char	*str = "Reset Stats ?";
	char	*str2 = STR_BUTTON_A " Yes       -       " STR_BUTTON_B " No";
	
	keynum_release(BUTTON_A);
	unbind_allkeys();
	keynum_replace(BUTTON_B, submenu_back);
	keynum_replace(BUTTON_A, _reset_yes);
	draw_text(str, 60 - (r_textwidth(str) / 2), 30, 0xFF);
	draw_text(str2, 60 - (r_textwidth(str2) / 2), 40, 0xFFFF);
}
