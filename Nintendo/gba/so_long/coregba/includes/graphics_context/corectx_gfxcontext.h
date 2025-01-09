/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corectx_gfxcontext.h                                                     */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 18:05:44 by NyTekCFW                                 */
/*   Updated: 21/12/2024 18:08:05 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORECTX_GFXCONTEXT_H
# define CORECTX_GFXCONTEXT_H

enum e_core_gcm
{
	GCM_FRONT	= 0,
	GCM_BACK,
	GCM_CURRENT,
	GCM_MAX
};

enum e_mode
{
	MODE_3_BG2	= 0x403, //1027
	MODE_4_BG2, //1028
	MODE_5_BG2 //1029
};

typedef struct core_gcm_s
{
	u8		current_buffer;
	vu16	*flip_status;
	u32		vbuf[GCM_MAX];
	u16		clear_color;
	u16		total_size;
}	t_gcm;


typedef struct mx_virtual_s
{
	u16	width;
	u16	height;
	u16	scaled_width;
	u16	scaled_height;
	u16	mode;
	u8	use_scaling;
	u8	timer_on;
}	t_virtual;

# include "corectx_gcm.h"
# include "corectx_virtual.h"

#endif