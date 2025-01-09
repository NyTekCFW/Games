/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_system.h                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 17:38:04 by NyTekCFW                                 */
/*   Updated: 20/12/2024 17:38:06 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_SYSTEM_H
# define CORESYS_SYSTEM_H

# define RESET_EWRAM				0x01
# define RESET_IWRAM				0x02
# define RESET_PALETTE			0x04
# define RESET_VRAM				0x08
# define RESET_OAM				0x10
# define RESET_SIO_REGS			0x20
# define RESET_SOUND_REGS		0x40
# define RESET_REGS				0x80
# define RESET_ALL				0xFF

# define CPU_FAST_SET_SRC_FIXED	0x01000000
# define CPU_SET_SRC_FIXED		0x01000000
# define CPU_SET_16BIT			0x00000000
# define CPU_SET_32BIT			0x04000000

# define REG_WAITCNT (*(vu16*)0x04000204)

# include "coresys_cpu.h"
# include "coresys_dma.h"
# include "coresys_malloc.h"
# include "coresys_clock.h"

#endif