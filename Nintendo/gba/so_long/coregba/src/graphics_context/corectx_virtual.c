/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corectx_virtual.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 17:06:44 by NyTekCFW                                 */
/*   Updated: 21/12/2024 17:59:23 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

t_virtual	*get_virtual(void)
{
	return (&get_core()->vmem);
}

static void	set_virtual_scale(void)
{
	u16	v = 256;//256=normal 128=scale 

	if (get_virtual()->use_scaling)
			v = 128;
	*(volatile u16 *)0x4000020 = v;//REG_BG2PA 
	*(volatile u16 *)0x4000026 = v;//REG_BG2PD
}

static void	set_virtual_mode(u8 scaled)
{
	t_virtual	*vmem = get_virtual();

	*(u16 *)0x4000000 = MODE_5_BG2;
	vmem->mode = MODE_5_BG2;
	vmem->use_scaling = scaled;
	vmem->width = 160;
	vmem->height = 128;
	vmem->scaled_width = (scaled) ? 120 : 160;
	vmem->scaled_height = (scaled) ? 80 : 128;
	set_virtual_scale();
}

static void	set_virtual_timer(void)
{
	t_virtual	*vmem = get_virtual();

	if (!vmem->timer_on)
	{
		clock_init();
		vmem->timer_on = 1;
	}
}

void	boot_virtual(u8 scaled)
{
	set_virtual_mode(scaled);
	set_virtual_timer();
}

