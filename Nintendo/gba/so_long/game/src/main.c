/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:17:53 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include "../includes/sounds/snd_popup.h"
#include "../includes/sounds/snd_main_menu.h"
#include "../includes/sounds/snd_dungeon.h"
#include "../includes/sounds/snd_link_attack.h"
#include "../includes/sounds/snd_trophy_unlock.h"

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
		if (get_submenu()->current_sub != SUB_CUSTOM_LVL)
			draw_rectangle(min_x, 1, n_w, 9, 0x3def, 1);
		draw_text(t, sw, 1, 0x7C7F);
		xfree((void **)&t);
	}
}

void	task_rendering(void)
{
	t_root	*root = get_root();

	if (root->gamestate.cl_ingame)
	{
		if (root->submenu.current_sub == SUB_CUSTOM_LVL)
			render_poc();
	}
	if (get_root()->settings.vars[VAR_SHOW_FPS])
		print_fpsx();
}

void	task_irq(void)
{

}

void	link_walk_pal_callback(u16 *pal)
{
	t_sav		*sav = get_sav();

	pal[1] = sav->user_data.skins[SKIN_JACKET];
	pal[2] = sav->user_data.skins[SKIN_BODY];
	pal[3] = sav->user_data.skins[SKIN_EQUIPMENTS];
}

void	link_melee_pal_callback(u16 *pal)
{
	t_sav		*sav = get_sav();

	pal[2] = sav->user_data.skins[SKIN_JACKET];
	pal[3] = sav->user_data.skins[SKIN_BODY];
	pal[1] = sav->user_data.skins[SKIN_EQUIPMENTS];
}

void	obj_pal_callback(u16 *pal)
{
	static u16 da = 0;

	if (clock() % 32)
		++da;
	if (da > 0x7fff)
		da = 1;
	pal[2] = da;
}

#define sizeof_array(array) (sizeof(array) / sizeof((array)[0]))

void	init_sprites(void)
{
	//player
	register_sprite("link_walk", pal_sprite_link_walks, 4, link_walk_pal_callback, sprite_link_walks, 16, 16, 8);
	register_sprite("link_melee_du", pal_sprite_link_melee, 8, link_melee_pal_callback, sprite_link_melee_du, 16, 28, 8);//down->up
	register_sprite("link_melee_rl", pal_sprite_link_melee, 8, link_melee_pal_callback, sprite_link_melee_rl, 28, 16, 8);//right->left	
	//obj
	register_sprite("obj", pal_sprites_obj, 3, obj_pal_callback, sprites_obj, 16, 16, 1);
}

void	init_sfx(void)
{
	//pregame
	register_sfx("snd_main_menu", snd_main_menu, 794172, true);// 4301,
	register_sfx("snd_popup", snd_popup, 6105, false);// 12,
	register_sfx("snd_trophy_unlocked", snd_trophy_unlocked, 10860, false);
	//in game
	register_sfx("snd_dungeon", snd_dungeon, 2118684, true);
	register_sfx("snd_link_attack", snd_link_attack, 2377, false);//12, 
}

void	init_gamedata(void)
{
	get_root();//init all basic data
	load_savedata();
	play_sfx("snd_main_menu");
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
	callback->reg_sfx = init_sfx;
	callback->initial_call = init_gamedata;
	run_tasks(1, 0x3def, 60, 1.0f, 0, SFX_11025_HZ);
}
