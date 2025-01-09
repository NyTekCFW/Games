/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_skin_color.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 21:37:21 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:15:27 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

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
	t_sprites	*poc = get_sprite("link_test");

	switch (*id)
	{
		case 0: poc->pal[1] = color; break;
		case 1: poc->pal[2] = color; break;
		case 2: poc->pal[3] = color; break;
	}
	draw_sprite(104, 63, 0, "link_test");
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
	keynum_replace(BUTTON_B, submenu_back);
}
