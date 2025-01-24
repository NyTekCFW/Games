/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_reset_stats.c                                                       */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:17:27 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	_reset_yes(void)
{
	t_sav		*sav = get_sav();
	t_stats		*stats = get_stats();
	u8			i = 0;

	xmemset(stats, 0, sizeof(t_stats));
	sav->user_data.skins[SKIN_JACKET] = 0x030b;
	sav->user_data.skins[SKIN_BODY] = 0x1e7f;
	sav->user_data.skins[SKIN_EQUIPMENTS] = 0x0178;
	while (i < TROPHY_MAX)
		get_trophy(i++)->unlocked = false;
	stats->ld[STATS_LD_LVL] = 1;
	try_unlock_trophy(TROPHY_NEW_START, NULL, NULL);
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
