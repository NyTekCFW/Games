/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corectx_gcm.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 17:06:44 by NyTekCFW                                 */
/*   Updated: 21/12/2024 17:59:20 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

t_gcm	*get_gcm(void)
{
	return (&get_core()->gcm);
}

void	gcm_setflip(void)
{
	t_gcm	*gcm = get_gcm();
	u8		n = 0;

	if (*gcm->flip_status & 0x10)
	{
		*gcm->flip_status &= ~0x10;
		n = GCM_BACK;
	}
	else
	{
		*gcm->flip_status |= 0x10;
		n = GCM_FRONT;
	}
	gcm->vbuf[GCM_CURRENT] = gcm->vbuf[n];
	gcm->current_buffer = n;
	*gcm->flip_status ^= 16;
}

u8	gcm_get_active_id(void)
{
	return (get_gcm()->current_buffer);
}

u16	gcm_get_buffer_size(void)
{
	return (get_gcm()->total_size);
}

u16	*gcm_get_active_buffer(void)
{
	return ((u16 *)get_gcm()->vbuf[GCM_CURRENT]);
}

u16	*gcm_get_draw_buffer(void)
{
	t_gcm	*gcm = get_gcm();

	return ((u16 *)gcm->vbuf[!gcm->current_buffer]);
}

u16	*gcm_get_front_buffer(void)
{
	return ((u16 *)get_gcm()->vbuf[GCM_FRONT]);
}

u16	*gcm_get_back_buffer(void)
{
	return ((u16 *)get_gcm()->vbuf[GCM_BACK]);
}

void	gcm_init_body(void)
{
	t_gcm	*gcm = get_gcm();

	gcm->vbuf[GCM_FRONT] = 0x6000000;
	gcm->vbuf[GCM_BACK] = 0x600A000;
	gcm->vbuf[GCM_CURRENT] = gcm->vbuf[GCM_FRONT];
	gcm->flip_status = (vu16 *)0x4000000;
	gcm->current_buffer = 0;
	gcm->clear_color = 0;
	gcm->total_size = 40960;
	if (get_virtual()->use_scaling)
		gcm->total_size = 25520;//25520 diff = 15440 ( / 1.605)
}

void	gcm_prepare_flip(void)
{
	while(REG_VCOUNT < 160)//// wait till VBlank
		;
	gcm_setflip();
}

void	gcm_clear_active_buffer(void)
{
	t_gcm	*gcm = get_gcm();
	
	CpuFill((u16 *)gcm->vbuf[GCM_CURRENT], gcm->clear_color, gcm->total_size);
}

void	gcm_clear_draw_buffer(void)
{
	t_gcm	*gcm = get_gcm();
	u16		*ptr = (u16 *)gcm->vbuf[!gcm->current_buffer];
	
	CpuFill(ptr, gcm->clear_color, gcm->total_size);
}

void	gcm_set_clear_color(u16 clr)
{
	get_gcm()->clear_color = clr;
}
