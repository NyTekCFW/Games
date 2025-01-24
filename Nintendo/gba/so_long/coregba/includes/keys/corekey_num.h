/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corekey_num.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 23:57:11 by NyTekCFW                                 */
/*   Updated: 20/12/2024 23:57:13 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREKEY_NUM_H
# define COREKEY_NUM_H

void	keynum_replace(u8 id, void (*(func))(void));
void	unbind_allkeys(void);
void	keynum_release_all(void);
void	unbind_keynum(u8 i);
void	keynum_release(u8 id);
void	freeze_controls(bool freeze);
bool	keynum_execute(u8 id);
bool	key_pressed(u16 key);
s8		get_key_num(u16 code);
t_key	*get_key(u8 id);

#endif