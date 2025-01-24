/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   game.c                                                                   */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:17:06 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

#define STRING_TO_ARRAY(str) { str }

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
			.cl_ingame = false,
			.in_pause = false
		},
		.settings =	{
			.vars[VAR_SHOW_FPS] = true,
			.vars[VAR_LIMIT_FPS] = false
		},
		.stats = {
			.ld[STATS_LD_LVL] = 55,
			.ld[STATS_LD_PRESTIGE] = 0,
			.ld[STATS_LD_XP] = 8250,
			.ld[STATS_LD_KILLS] = 0,
			.ld[STATS_LD_DEATHS] = 0,
			.ld[STATS_LD_RUPPIES] = 0,
			.ld[STATS_LD_CLEARED_LVL] = 0,
			.ld[STATS_LD_TIME] = 3599999
		},
		.sav = {
			.header.coregba_version = COREGBA_VERSION,
			.header.game_version = GAME_VERSION,
			.user_data.skins[SKIN_JACKET] = 0x030b,
			.user_data.skins[SKIN_BODY] = 0x1e7f,
			.user_data.skins[SKIN_EQUIPMENTS] = 0x0178,
			0
		},
		.user = {
			.step = 0,
			.flags = 0,
			.dir_id = 0,
			.health = 100,
			.dir_flags = 0,
			.max_health = 100,
			.cam_addon = {0, 0},
			.camera = {.x = 0, .y = 0},
			.origin = {.x = 0, .y = 0},
			.cur_tile = 0
		},
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
				[SUB_CUSTOM_LVL] = submenu_map_custom,
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
		},
		.custom_map = {
			[0] = {.in_use = false,.name = STRING_TO_ARRAY("Custom 1"),.l_data = NULL},
			[1] = {.in_use = false,.name = STRING_TO_ARRAY("Custom 2"),.l_data = NULL},
			[2] = {.in_use = false,.name = STRING_TO_ARRAY("Custom 3"),.l_data = NULL},
			[3] = {.in_use = false,.name = STRING_TO_ARRAY("Custom 4"),.l_data = NULL},
			[4] = {.in_use = false,.name = STRING_TO_ARRAY("Custom 5"),.l_data = NULL},
		}
	};
	return (&root);
}

t_submenu	*get_submenu(void)
{
	return (&get_root()->submenu);
}

t_area_info	*get_area_info(void)
{
	return (&get_root()->area_info);
}

t_stats	*get_stats(void)
{
	return (&get_root()->stats);
}

t_sav	*get_sav(void)
{
	return (&get_root()->sav);
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

t_user	*get_user(void)
{
	return (&get_root()->user);
}
