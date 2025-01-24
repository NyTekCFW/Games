/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_sav.c                                                                 */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:16:50 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	copy_localdata_to_sav(void)
{
	u8			trophy_inc = 0;
	u8			stats_inc = 0;
	t_sav		*sav = get_sav();
	t_root		*root = get_root();

	sav->header = root->gameinfo;
	while (trophy_inc < TROPHY_MAX)
	{
		sav->user_data.trophies[trophy_inc] = get_trophy(trophy_inc)->unlocked;
		++trophy_inc;
	}
	while (stats_inc < STATS_LD_MAX)
	{
		sav->user_data.ld[stats_inc] = get_stats()->ld[stats_inc];
		++stats_inc;
	}
}

static void	copy_sav_to_localdata(void)
{
	u8			trophy_inc = 0;
	u8			stats_inc = 0;
	t_sav		*sav = get_sav();

	while (trophy_inc < TROPHY_MAX)
	{
		get_trophy(trophy_inc)->unlocked = sav->user_data.trophies[trophy_inc];
		++trophy_inc;
	}
	while (stats_inc < STATS_LD_MAX)
	{
		get_stats()->ld[stats_inc] = sav->user_data.ld[stats_inc];
		++stats_inc;
	}
}

static bool	_check_sav(void)
{
	t_gameinfo	*header = get_gameinfo();
	t_gameinfo	tmp = { 0 };

	load_from_eeprom(&tmp, 0, sizeof(t_gameinfo));
	return (tmp.game_version == header->game_version
		&& tmp.coregba_version == header->coregba_version);
}

void	build_savedata(void)
{
	t_sav	*sav = get_sav();

	copy_localdata_to_sav();
	save_to_eeprom(sav, 0, sizeof(t_sav));
}

void	load_savedata(void)
{
	t_sav	*sav = get_sav();

	if (_check_sav())
	{
		load_from_eeprom(sav, 0, sizeof(t_sav));
		copy_sav_to_localdata();
	}
}
