/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coretask_run.c                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:14:36 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static void	_register_sprites(void)
{
	t_callback	*callback = get_callback();

	register_sprite("buttons_8x8", pal_buttons_8x8, 5, NULL, sprite_buttons_8x8, 8, 8, 9);
	register_sprite("buttons_16x8", pal_buttons_8x8, 5, NULL, sprite_buttons_16x8, 16, 8, 2);
	register_sprite("buttons_24x8", pal_buttons_8x8, 5, NULL, sprite_buttons_24x8, 24, 8, 2);
	register_sprite("buttons_check_8x8", pal_buttons_check_8x8, 3, NULL, sprite_buttons_check_8x8, 8, 8, 2);
	register_sprite("buttons_trophy_8x8", pal_buttons_trophy_8x8, 6, NULL, sprite_buttons_trophy_8x8, 8, 8, 4);
	register_sprite("color_picker_bkg", pal_color_picker_bkg, 7, NULL, sprite_color_picker_bkg, 26, 26, 1);
	if (callback->reg_sprites)
		callback->reg_sprites();
}

static void	_register_sfx(enum e_sfx_hz hz)
{
	t_callback	*callback = get_callback();

	set_audio_hz(hz);
	if (callback->reg_sfx)
		callback->reg_sfx();
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
	}
	engine->initialised = 0;
}

void	run_tasks(u8 scaled, u16 clear_color, u8 max_fps, float timescale, u32 rand_seed, enum e_sfx_hz hz)
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
	xsrand(rand_seed);
	engine->initialised = 1;
	engine->running = 1;
	engine->max_fps = (max_fps < 3) ? 60 : max_fps;
	engine->timescale = (timescale < 0.3) ? 1.0f : \
		((timescale > 2.0f) ? 1.0f : timescale);
	engine->backup_fps = max_fps;
	_register_sprites();
	_register_sfx(hz);
	if (callback->initial_call)
		callback->initial_call();
	run_task_irq();
	run_engine();
}
