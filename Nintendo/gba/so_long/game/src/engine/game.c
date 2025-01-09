/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   game.c                                                                   */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 17:21:34 by NyTekCFW                                 */
/*   Updated: 27/12/2024 17:22:41 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

t_root	*get_root(void)
{
	static t_root	root =
	{
		.gameinfo =	{
			.coregba_version = COREGBA_VERSION,
			.game_version = GAME_VERSION
		},
		.gamestate = {
			.status = 0,
			.in_pause = false
		},
		.settings =	{
			.show_fps = false,
			.limit_fps = true
		},
		.stats = { 9999999,.ld[STATS_LD_PRESTIGE] = 9999999, },
		.save = { 0 },
		.submenu =	{
			.current_scroll = 0,
			.current_sub = 0,
			.prev_count = 0,
			.prev_scroll = { 0 },
			.prev_sub = { 0 },
			.entries = {
				[SUB_MAIN_MENU] = submenu_main_menu,
				[SUB_LVL_SELECT] = submenu_play,
				[SUB_SKIN_COLOR] = submenu_skin_color,
				[SUB_CUSTOM_LVL] = NULL,
				[SUB_OPTIONS] = submenu_options,
				[SUB_CONTROLS] = submenu_controls,
				[SUB_TROPHIES] = submenu_trophies,
				[SUB_STATS] = submenu_stats,
				[SUB_RESET_STATS] = submenu_reset_stats
			}
		},
		.trophies =	{
			[TROPHY_HUNTER] = {.unlocked = false, .rarity = 1},
			[TROPHY_COLLECTOR] = {.unlocked = false, .rarity = 1},
			[TROPHY_BEGINNER] = {.unlocked = false, .rarity = 1},
			[TROPHY_EXPERT] = {.unlocked = false, .rarity = 2},
			[TROPHY_FINISHER] = {.unlocked = false, .rarity = 2},
			[TROPHY_MAKER] = {.unlocked = false, .rarity = 1},
			[TROPHY_NEW_START] = {.unlocked = false, .rarity = 1},
			[TROPHY_EXPLORER] = {.unlocked = false, .rarity = 2},
			[TROPHY_STYLIST] = {.unlocked = false, .rarity = 1},
			[TROPHY_ENDGAME] = {.unlocked = false, .rarity = 3}
		}
	};
	return (&root);
}

t_submenu	*get_submenu(void)
{
	return (&get_root()->submenu);
}

t_stats	*get_stats(void)
{
	return (&get_root()->stats);
}

t_save	*get_save(void)
{
	return (&get_root()->save);
}

t_trophy	*get_trophies(void)
{
	return (get_root()->trophies);
}

t_trophy	*get_trophy(u8 index)
{
	if (index < TROPHY_MAX)
		return (&get_root()->trophies[index]);
	return (NULL);
}

t_settings	*get_settings(void)
{
	return (&get_root()->settings);
}

t_gameinfo	*get_gameinfo(void)
{
	return (&get_root()->gameinfo);
}

t_gamestate	*get_gamestate(void)
{
	return (&get_root()->gamestate);
}
