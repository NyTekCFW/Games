/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_save.c                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 01/01/2025 04:36:55 by NyTekCFW                                 */
/*   Updated: 01/01/2025 04:36:58 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

/*
//v1.0.0 save structure for backporting
typedef struct	skin_v100_s
{
	u16	clr_jacket;
	u16	clr_skin;
	u16	clr_equipment;
}	t_skin_v100;

typedef struct user_v100_s
{
	bool	trophies[20];
}	t_user_v100;

typedef struct save_v100_s
{
	t_gameinfo		header;//header for game version detection
	t_skin_v100		skin;
	t_user_v100		user;
}	t_save_v100;


void	load_save(void)
{
	t_gameinfo	*header = get_gameinfo();
	t_gameinfo	tmp = { 0 };

	load_from_eeprom(&tmp, 0, sizeof(t_gameinfo));
	if (tmp.game_version != header->game_version)
	{
		//update old save to new save format
		switch (tmp.game_version)
		{
			case 100: break; // v1.0.0
			default: return ;
		}
	}
	else
	{
		load_from_eeprom(get_save(), 0, sizeof(t_save));
		//apply save settings to game
	}
}

void	save_game(void)
{
	t_save	*sav = get_save();
}
*/