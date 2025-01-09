/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_controls.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 27/12/2024 22:42:55 by NyTekCFW                                 */
/*   Updated: 29/12/2024 04:14:48 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	submenu_controls(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_B, submenu_back);
	draw_text(STR_BUTTON_B " Back", 2, 71, 0xFFFF);
	draw_text(STR_DPAD_NONE " Move\n" STR_BUTTON_B " Attack\n" STR_BUTTON_A " Interact\n" STR_BUTTON_START " Pause\n"\
	STR_BUTTON_SELECT " Minimap", 2, 2, 0xFFFF);
}
