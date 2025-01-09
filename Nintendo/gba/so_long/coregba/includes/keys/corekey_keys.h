/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corekey_keys.h                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/12/2024 16:28:03 by NyTekCFW                                 */
/*   Updated: 20/12/2024 23:52:22 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREKEY_KEYS_H
# define COREKEY_KEYS_H

enum e_button
{
	BUTTON_A	= 0,
	BUTTON_B,
	BUTTON_L,
	BUTTON_R,
	BUTTON_START,
	BUTTON_SELECT,
	BUTTON_MOVE_FORWARD,
	BUTTON_MOVE_BACKWARD,
	BUTTON_MOVE_LEFT,
	BUTTON_MOVE_RIGHT,
	BUTTON_MAX
};

typedef struct key_hook_s
{
	u16		code;
	u8		id;
	bool	ignore;
	bool	is_pressed;
	void	(*(callback))(void);
}	t_key;

# include "corekey_code.h"
# include "corekey_num.h"
#endif