/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corekey_code.h                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 23:52:06 by NyTekCFW                                 */
/*   Updated: 20/12/2024 23:52:10 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREKEY_CODE_H
# define COREKEY_CODE_H

void	set_keycode_status(u16 code, bool active);
void	add_keycode(u8 id, u16 code, void (*(func))(void));
void	init_keyboard(void);
bool	keycode_pressed(u16 code);

#endif