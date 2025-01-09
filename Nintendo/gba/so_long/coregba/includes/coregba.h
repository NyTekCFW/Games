/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregba.h                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 17:06:44 by NyTekCFW                                 */
/*   Updated: 21/12/2024 18:28:18 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MX_GLOBAL_H
# define MX_GLOBAL_H

#ifdef CONSOLE_MODE
# include </opt/devkitpro/libgba/include/gba_console.h>
//consoleDemoInit();
#endif

# define COREGBA_VERSION	101
# define ALIGNED(n) __attribute__((aligned(n)))

# include </opt/devkitpro/libgba/include/gba_types.h>
# include </opt/devkitpro/libgba/include/gba_video.h>
# include </opt/devkitpro/libgba/include/gba_interrupt.h>
# include </opt/devkitpro/libgba/include/gba_systemcalls.h>
# include </opt/devkitpro/libgba/include/gba_dma.h>
# include </opt/devkitpro/libgba/include/gba_input.h>

# include "./system/coresys_system.h"
# include "./utils/coreutil_utils.h"
# include "./keys/corekey_keys.h"
# include "./graphics_context/corectx_gfxcontext.h"
# include "./graphics/coregfx_graphics.h"
# include "./tasks/coretask_tasks.h"
# include "./savedata/coresave_savedata.h"

enum e_action
{
	ACT_INIT	= 0,
	ACT_GET,
	ACT_FREE
};

typedef struct core_s
{
	t_virtual	vmem;
	t_gcm		gcm;
	t_callback	callback;
	t_key		key[BUTTON_MAX];
	t_engine	engine;
	t_texture	texture;
	t_cp		color_picker;
}	t_core;

t_core		*get_core(void);
t_callback	*get_callback(void);
t_engine	*get_engine(void);
t_texture	*get_texture(void);
t_cp		*get_color_picker(void);
#endif
