/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_trophies.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:16:59 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char	*get_trophy_name(u8 index)
{
	switch (index)
	{
		case TROPHY_HUNTER: return ("The Hunter");
		case TROPHY_COLLECTOR: return ("Collector");
		case TROPHY_BEGINNER: return ("Beginner");
		case TROPHY_EXPERT: return ("Expert");
		case TROPHY_FINISHER: return ("The Finisher");
		case TROPHY_MAKER: return ("The Maker");
		case TROPHY_NEW_START: return ("New Start");
		case TROPHY_EXPLORER: return ("Explorer");
		case TROPHY_STYLIST: return ("Stylist");
		case TROPHY_ENDGAME: return ("End Game");
		default: return ("N/A");
	}
	return (NULL);
}

bool	try_unlock_trophy(u8 index, bool (*check_func)(void *), void *param)
{
	bool		c = false;
	t_trophy	*trophy = get_trophy(index);

	if (index >= TROPHY_MAX || !trophy || trophy->unlocked)
		return (false);
	c = (check_func == NULL || check_func(param));
	if (c)
	{
		trophy->unlocked = true;
		play_sfx("snd_trophy_unlocked");
	}
	return (c);
}
