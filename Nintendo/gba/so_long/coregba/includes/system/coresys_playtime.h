/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_playtime.h                                                       */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/01/2025 04:03:29 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:11:56 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_PLAYTIME_H
# define CORESYS_PLAYTIME_H

typedef struct playtime_s
{
	u32	day;
	u32	hoor;
	u32	min;
	u32	sec;
	u32	format;
}ALIGNED(4)	t_playtime;

enum e_playtime_format
{
	PLAYTIME_FORMAT_D_HH_MM_SS		= (1 << 0),  // Format: d:hh:mm:ss
	PLAYTIME_FORMAT_HH_MM_SS		= (1 << 1),  // Format: hh:mm:ss
	PLAYTIME_FORMAT_MM_SS			= (1 << 2),  // Format: mm:ss
	PLAYTIME_FORMAT_DAYS_HOURS		= (1 << 3),  // Format: d:hh
	PLAYTIME_FORMAT_HOURS_MINUTES	= (1 << 4),  // Format: hh:mm
	PLAYTIME_FORMAT_MINUTES			= (1 << 5),  // Format: mm
	PLAYTIME_FORMAT_DAYS			= (1 << 6),  // Format: d
	PLAYTIME_FORMAT_HOURS			= (1 << 7),  // Format: hh
	PLAYTIME_FORMAT_SECONDS			= (1 << 8),   // Format: second
	PLAYTIME_FORMAT_ADAPTIVE		= (1 << 9)
};

t_playtime	*get_playtime(t_playtime *buffer, u32 seconds, enum e_playtime_format flag);
char		*get_playtime_str_format(u32 second, enum e_playtime_format flag);
#endif