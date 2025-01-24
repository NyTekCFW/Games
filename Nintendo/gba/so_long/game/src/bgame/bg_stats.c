/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_stats.c                                                               */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 03/01/2025 03:55:44 by NyTekCFW                                 */
/*   Updated: 03/01/2025 03:55:46 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char	*get_stat_info(u8 index)
{
	t_stats		*stats = get_stats();
	char		*tmp = NULL;
	char		*str = NULL;

	switch(index)
	{
		case STATS_LD_LVL: return (va_alloc("Level :%u", stats->ld[STATS_LD_LVL]));
		case STATS_LD_PRESTIGE: return (va_alloc("Prestige :%u", stats->ld[STATS_LD_PRESTIGE]));
		case STATS_LD_XP: return (va_alloc("XP :%u/%u", stats->ld[STATS_LD_XP], stats->ld[STATS_LD_LVL] * 150));
		case STATS_LD_KILLS: return (va_alloc("Kills :%u", stats->ld[STATS_LD_KILLS]));
		case STATS_LD_DEATHS: return (va_alloc("Deaths :%u", stats->ld[STATS_LD_DEATHS]));
		case STATS_LD_RUPPIES: return (va_alloc("Ruppies :%u", stats->ld[STATS_LD_RUPPIES]));
		case STATS_LD_CLEARED_LVL: return (va_alloc("Cleared :%u", stats->ld[STATS_LD_CLEARED_LVL]));
		case STATS_LD_TIME:
		{
			tmp = get_playtime_str_format(stats->ld[STATS_LD_TIME], PLAYTIME_FORMAT_HOURS_MINUTES);
			str = va_alloc("Time:%s", tmp);
			xfree((void **)&tmp);
			return (str);
		}
		default: return (NULL);
	}
	return (NULL);
}