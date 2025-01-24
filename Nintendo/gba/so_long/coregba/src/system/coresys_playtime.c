/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_playtime.c                                                       */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/01/2025 04:02:34 by NyTekCFW                                 */
/*   Updated: 11/01/2025 04:02:35 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

t_playtime *get_playtime(t_playtime *buffer, u32 seconds, enum e_playtime_format flag)
{
	if (flag & PLAYTIME_FORMAT_ADAPTIVE)
	{
		if (seconds < 60)
			flag = PLAYTIME_FORMAT_SECONDS;
		else if (seconds < 3600)
			flag = PLAYTIME_FORMAT_MM_SS;
		else if (seconds < 86400)
			flag = PLAYTIME_FORMAT_HOURS_MINUTES;
		else
			flag = PLAYTIME_FORMAT_DAYS_HOURS;
	}
	if (flag & PLAYTIME_FORMAT_D_HH_MM_SS)
	{
		buffer->day = seconds / 86400;
		seconds %= 86400;
		buffer->hoor = seconds / 3600;
		seconds %= 3600;
		buffer->min = seconds / 60;
		buffer->sec = seconds % 60;
	}
	else if (flag & PLAYTIME_FORMAT_HH_MM_SS)
	{
		buffer->day = 0;
		buffer->hoor = seconds / 3600;
		seconds %= 3600;
		buffer->min = seconds / 60;
		buffer->sec = seconds % 60;
	}
	else if (flag & PLAYTIME_FORMAT_MM_SS)
	{
		buffer->day = 0;
		buffer->hoor = 0;
		buffer->min = seconds / 60;
		buffer->sec = seconds % 60;
	}
	else if (flag & PLAYTIME_FORMAT_DAYS_HOURS)
	{
		buffer->day = seconds / 86400;
		buffer->hoor = (seconds % 86400) / 3600;
	}
	else if (flag & PLAYTIME_FORMAT_HOURS_MINUTES)
	{
		buffer->hoor = seconds / 3600;
		buffer->min = (seconds % 3600) / 60;
	}
	else if (flag & PLAYTIME_FORMAT_MINUTES)
		buffer->min = seconds / 60;
	else if (flag & PLAYTIME_FORMAT_DAYS)
		buffer->day = seconds / 86400;
	else if (flag & PLAYTIME_FORMAT_HOURS)
		buffer->hoor = seconds / 3600;
	else if (flag & PLAYTIME_FORMAT_SECONDS)
		buffer->sec = seconds % 60;
	buffer->format = flag;
    return (buffer);
}

char	*get_playtime_str_format(u32 second, enum e_playtime_format flag)
{
	t_playtime	time = {0};

	get_playtime(&time, second, flag);
	switch (time.format)
	{
		case PLAYTIME_FORMAT_D_HH_MM_SS: return (va_alloc("%u:%02u:%02u:%02u", time.day, time.hoor, time.min, time.sec));
		case PLAYTIME_FORMAT_HH_MM_SS: return (va_alloc("%02u:%02u:%02u", time.hoor, time.min, time.sec));
		case PLAYTIME_FORMAT_MM_SS: return (va_alloc("%02u:%02u", time.min, time.sec));
		case PLAYTIME_FORMAT_DAYS_HOURS: return (va_alloc("%u:%02u", time.day, time.hoor));
		case PLAYTIME_FORMAT_HOURS_MINUTES: return (va_alloc("%02u:%02u", time.hoor, time.min));
		case PLAYTIME_FORMAT_MINUTES: return (va_alloc("%02u", time.min));
		case PLAYTIME_FORMAT_DAYS: return (va_alloc("%u", time.day));
		case PLAYTIME_FORMAT_HOURS: return (va_alloc("%02u", time.hoor));
		case PLAYTIME_FORMAT_SECONDS: return (va_alloc("%02u", time.sec));
		default: return (NULL);
	}
	return (NULL);
}

/*
t_playtime	*get_playtime(t_playtime *buffer, u32 seconds)
{
	buffer->day = seconds / 86400;
	seconds %= 86400;
	buffer->hoor = seconds / 3600;
	seconds %= 3600;
	buffer->min = seconds / 60;
	buffer->sec = seconds % 60;
	return (buffer);
}

*/
