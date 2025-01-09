/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:08:08 by NyTekCFW                                 */
/*   Updated: 09/12/2024 09:10:57 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
/*
void	dump_palette(void)
{
	u16	*vbuf = (u16 *)0x05000000;
	u16	*dump = mx_malloc(256 * sizeof(short));

	CpuCopy16((void *)vbuf, (void *)dump, 256 * sizeof(u16));
	for (u32 i = 0; i < 256; ++i)
	{
		dump[i] = (dump[i] >> 8) | (dump[i] << 8);
	}
}
*/

/*
void	dump_screen_section(int x, int y, int w, int h)
{
	u16	*vbuf = gcm_get_draw_buffer();
	u16	*dump = mx_malloc((w * h) * sizeof(short));

	for (int y2 = 0; y2 < h; ++y2)
	{
		const u16 *src = &vbuf[((y + y2) * get_virtual()->width) + x];
		u16 *dst = &dump[y2 * h];
		CpuCopy16((void *)src, (void *)dst, w * sizeof(u16));
	}

	u32 size = w * h;
	for (u32 i = 0; i < size; ++i)
	{
		dump[i] = (dump[i] >> 8) | (dump[i] << 8);
	}
}
*/

void	task_key_init(void)
{
	add_keycode(BUTTON_A, KEY_A, NULL);
	add_keycode(BUTTON_B, KEY_B, NULL);
	add_keycode(BUTTON_L, KEY_L, NULL);
	add_keycode(BUTTON_R, KEY_R, NULL);
	add_keycode(BUTTON_START, KEY_START, NULL);
	add_keycode(BUTTON_SELECT, KEY_SELECT, NULL);
	add_keycode(BUTTON_MOVE_FORWARD, KEY_UP, NULL);
	add_keycode(BUTTON_MOVE_BACKWARD, KEY_DOWN, NULL);
	add_keycode(BUTTON_MOVE_LEFT, KEY_LEFT, NULL);
	add_keycode(BUTTON_MOVE_RIGHT, KEY_RIGHT, NULL);
}

void	task_scripts(void)
{

}

void	print_fpsx(void)
{
	static u16	min_x = 0xFFFF;
	static u16	n_w = 0;
	t_virtual	*virtual = get_virtual();
	t_engine	*engine = get_engine();
	char		*t = xitoa(engine->fps_out);
	u16			w = 0;
	u16			sw = 0;

	if (t)
	{
		w = (u16)r_textwidth(t);
		sw = virtual->scaled_width - w;
		if (sw < min_x)
		{
			min_x = sw;
			n_w = (virtual->scaled_width - 1) - min_x;
		}
		draw_rectangle(min_x, 1, n_w, 9, 0x3def, 1);
		draw_text(t, sw, 1, 0x7C7F);
		xfree((void **)&t);
	}
}

void	task_rendering(void)
{

	if (get_root()->settings.show_fps)
		print_fpsx();
}

void	task_irq(void)
{

}

void	init_sprites(void)
{
	register_sprite("link_test", pal_sprite_link_walks, sprite_link_walks, 16, 16, 8);
}

void	init_gamedata(void)
{
	get_root();//init all basic data
	//tmp save to check if its valid
	//if valid copy tmp to true save
	submenu_set(SUB_MAIN_MENU);
}

int main(void)
{
	t_callback	*callback = get_callback();

	callback->scripts = task_scripts;
	callback->rendering = task_rendering;
	callback->keys = task_key_init;
	callback->irq = task_irq;
	callback->reg_sprites = init_sprites;
	callback->initial_call = init_gamedata;
	run_tasks(1, 0x3def, 60, 1.0f, 0);
}
