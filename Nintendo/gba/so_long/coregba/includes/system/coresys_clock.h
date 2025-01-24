/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_clock.h                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 19:58:22 by NyTekCFW                                 */
/*   Updated: 20/12/2024 19:58:23 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_CLOCK_H
# define CORESYS_CLOCK_H

# define REG_TM0CNT				(*(vu16 *)0x4000102)
# define REG_TM0D				(*(vu16 *)0x4000100)
# define REG_TM1D				(*(vu16 *)0x4000104)
# define REG_TM1CNT				(*(vu16 *)0x4000106)
# define REG_TM2D				(*(vu16 *)0x4000108)
# define REG_TM2CNT				(*(vu16 *)0x400010A)
# define REG_TM3D				(*(vu16 *)0x400010C)
# define REG_TM3CNT				(*(vu16 *)0x400010E)

# define TIMER_ENABLE			0x0080
# define TIMER_IRQ_ENABLE		0x40
# define TIMER_FREQ_1			0x0000
# define TIMER_FREQ_64			0x0001
# define TIMER_FREQ_256			0x0002
# define TIMER_FREQ_1024		0x0003
# define TIMER_CASCADE			0x0004
# define CLOCKS_PER_SEC			0x10000

void		clock_init(void);
void		sleep(float sec);
bool		clock_waittime(u32 wait);
u32			clock(void);
u32			get_fps(u32 cpu);

#endif