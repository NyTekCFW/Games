/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_trophies.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 01/01/2025 03:46:47 by NyTekCFW                                 */
/*   Updated: 01/01/2025 03:46:48 by NyTekCFW                                 */
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
