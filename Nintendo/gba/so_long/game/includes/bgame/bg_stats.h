/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_stats.h                                                               */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:15:18 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_STATS_H
# define BG_STATS_H

enum e_stats_ld
{
	STATS_LD_LVL			= 0,
	STATS_LD_PRESTIGE,
	STATS_LD_XP,
	STATS_LD_KILLS,
	STATS_LD_DEATHS,
	STATS_LD_RUPPIES,
	STATS_LD_CLEARED_LVL,
	STATS_LD_TIME,
	STATS_LD_MAX
};

typedef struct stats_s
{
	u32		ld[STATS_LD_MAX];
}ALIGNED(4)	t_stats;

char	*get_stat_info(u8 index);

#endif