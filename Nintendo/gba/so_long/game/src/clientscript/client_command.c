/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   client_command.c                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 26/12/2024 23:07:56 by NyTekCFW                                 */
/*   Updated: 26/12/2024 23:07:57 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	pcommand_mm_stats(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_B, NULL);
}

void	pcommand_mm_create_lvl(void)
{
	unbind_allkeys();
	keynum_replace(BUTTON_A, NULL);
	keynum_replace(BUTTON_L, NULL);
	keynum_replace(BUTTON_R, NULL);
	keynum_replace(BUTTON_START, NULL);
	keynum_replace(BUTTON_SELECT, NULL);
}

