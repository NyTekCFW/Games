/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_skin_color.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:17:33 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static bool	can_unlock(void *data)
{
	t_sav	*sav = (t_sav *)data;

	return (sav->user_data.skins[SKIN_JACKET] != 0x030b
			&& sav->user_data.skins[SKIN_BODY] != 0x1e7f
			&& sav->user_data.skins[SKIN_EQUIPMENTS] != 0x0178);
}

static void	callback_back(void)
{
	t_trophy	*trophy = get_trophy(TROPHY_STYLIST);

	try_unlock_trophy(TROPHY_STYLIST, can_unlock, get_sav());
	build_savedata();
	submenu_back();
}

static u8	*get_skin_id(void)
{
	static u8	skin_id = 0;

	return (&skin_id);
}

static void	skin_switch(void)
{
	char	*str[3] = { "Jacket", "Skin", "Equipment" };
	u8		*id = get_skin_id();

	*id = ((*id + 1) % 3);
	keynum_release(BUTTON_A);
	draw_rectangle(2, 2, r_textwidth(str[2]), r_glyph_height(), 0x3def, 1);
	draw_text(str[*id], 2, 2, 0xFFFF);
}

static void	skin_color_update(u8 row, u8 col, u16 color)
{
	u8			*id = get_skin_id();
	t_sav		*sav =get_sav();

	sav->user_data.skins[*id] = color;
	draw_sprite(103, 63 - 32, 0, "link_melee_du");
	draw_sprite(103, 63 - 16, 0, "link_melee_rl");
	draw_sprite(103, 63, 0, "link_walk");
}

void	submenu_skin_color(void)
{
	t_cp	*cp = get_color_picker();

	keynum_release(BUTTON_A);
	draw_text(STR_BUTTON_A " Next\n" STR_DPAD_LEFT_RIGHT " Color\n" STR_DPAD_UP_DOWN " Brightness\n" STR_BUTTON_B " Back", 2, 44, 0xffff);
	draw_text("Jacket", 2, 2, 0xFFFF);
	*get_skin_id() = 0;
	cp->p_x = 46;
	cp->p_y = 23;
	cp->callback = skin_color_update;
	open_color_picker();
	keynum_replace(BUTTON_A, skin_switch);
	keynum_replace(BUTTON_B, callback_back);
}
