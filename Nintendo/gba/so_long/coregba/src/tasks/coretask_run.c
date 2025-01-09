/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coretask_run.c                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 18:35:01 by NyTekCFW                                 */
/*   Updated: 21/12/2024 19:14:05 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static void	_register_sprites(void)
{
	t_callback	*callback = get_callback();

	register_sprite("buttons_8x8", pal_buttons_8x8, sprite_buttons_8x8, 8, 8, 9);
	register_sprite("buttons_16x8", pal_buttons_8x8, sprite_buttons_16x8, 16, 8, 2);
	register_sprite("buttons_24x8", pal_buttons_8x8, sprite_buttons_24x8, 24, 8, 2);
	register_sprite("buttons_check_8x8", pal_buttons_check_8x8, sprite_buttons_check_8x8, 8, 8, 2);
	register_sprite("buttons_trophy_8x8", pal_buttons_trophy_8x8, sprite_buttons_trophy_8x8, 8, 8, 4);
	if (callback->reg_sprites)
		callback->reg_sprites();
}

static void	run_engine(void)
{
	t_engine	*engine = get_engine();
	t_callback	*callback = get_callback();

	while (engine->running)
	{
		if (callback->scripts)
			callback->scripts();
		run_task_rendering(engine, callback);
		gcm_prepare_flip();
		CpuCopy(gcm_get_draw_buffer(), gcm_get_active_buffer(), gcm_get_buffer_size());
	}
	engine->initialised = 0;
}

void	run_tasks(u8 scaled, u16 clear_color, u8 max_fps, float timescale, u32 rand_seed)
{
	t_engine	*engine = get_engine();
	t_callback	*callback = get_callback();

	boot_virtual(scaled);
	gcm_init_body();
	gcm_set_clear_color(clear_color);
	gcm_clear_draw_buffer();
	init_keyboard();
	if (callback->keys)
		callback->keys();
	run_task_irq();
	xsrand(rand_seed);
	engine->initialised = 1;
	engine->running = 1;
	engine->max_fps = (max_fps < 3) ? 60 : max_fps;
	engine->timescale = (timescale < 0.3) ? 1.0f : \
		((timescale > 2.0f) ? 1.0f : timescale);
	_register_sprites();
	if (callback->initial_call)
		callback->initial_call();
	run_engine();
}
