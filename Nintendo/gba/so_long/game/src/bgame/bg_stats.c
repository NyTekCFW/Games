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

static char	*get_stat_name(u8 index)
{
	switch(index)
	{
		case STATS_LD_LVL: return ("Level :");
		case STATS_LD_PRESTIGE: return ("Prestige :");
		case STATS_LD_XP: return ("XP :");
		case STATS_LD_KILLS: return ("Kills :");
		case STATS_LD_DEATHS: return ("Deaths :");
		case STATS_LD_RUPPIES: return ("Ruppies :");
		case STATS_LD_CLEARED_LVL: return ("Cleared :");
		default: return ("N/A");
	}
	return (NULL);
}

static char	*get_stat_str_value(u8 index)
{
	t_stats	*stats = get_stats();

	if (index < STATS_LD_MAX)
		return (xitoa(stats->ld[index]));
	return (NULL);
}

char	*get_stat_info(u8 index)
{
	char	*name = get_stat_name(index);
	char	*info = get_stat_str_value(index);
	char	*buffer = NULL;
	u32		len = 0;

	if (name)
	{
		if (info)
		{
			len = xstrlen(name) + xstrlen(info) + 1;
			if (xalloc((void **)&buffer, len, sizeof(char)))
			{
				xstrcpy(buffer, name);
				xstrcpy(&buffer[xstrlen(buffer)], info);
			}
			xfree((void **)&info);
		}
	}
	return (buffer);
}
