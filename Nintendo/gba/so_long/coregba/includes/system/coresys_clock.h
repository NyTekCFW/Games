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

# define CLOCKS_PER_SEC	0x10000

void	clock_init(void);
void	sleep(float sec);
bool	clock_waittime(u32 wait);
u32		clock(void);
u32		get_fps(u32 cpu);

#endif