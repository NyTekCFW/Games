/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_clock.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/12/2024 09:59:00 by NyTekCFW                                 */
/*   Updated: 20/12/2024 20:00:29 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

#define	TIME_LIMIT 0xFF000000

void	clock_init(void)
{
	REG_TM2D = 0;
	REG_TM3D = 0;
	REG_TM2CNT = (TIMER_ENABLE | TIMER_FREQ_256);
	REG_TM3CNT = (TIMER_ENABLE | TIMER_CASCADE);//anti timer overflow
}

u32	clock(void)
{
	u16			TM2CNT_L = REG_TM2D;
	u16			TM3CNT_L = REG_TM3D;
	u32	TM4CNT = (TM3CNT_L << 16 | TM2CNT_L);

	if (TM4CNT >= TIME_LIMIT)
		clock_init();
	return (TM4CNT);
}

bool	clock_waittime(u32 wait)
{
	if (wait >= TIME_LIMIT) //overflow fix
	{
		wait = wait % TIME_LIMIT;
		return (clock_init(), 1);
	}
	return (clock() >= wait);
}

u32	get_fps(u32 cpu)
{
	float	s = 0;

	cpu = clock() - cpu;
	s = (float)cpu / CLOCKS_PER_SEC;
	return ((1 / s));
}

void	sleep(float sec)
{
	u32	f = clock();

	if (sec < 0.0001f)
		return ;
	sec = (u32)(CLOCKS_PER_SEC * sec);
	while ((clock() - f) < sec)
		;
}
