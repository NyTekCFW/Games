/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corekey_num.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/12/2024 17:27:59 by NyTekCFW                                 */
/*   Updated: 20/12/2024 23:50:10 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

s8	get_key_num(u16 code)
{
	s8	i = -1;

	while (++i < BUTTON_MAX)
	{
		if (get_core()->key[i].code == code)
			return (i);
	}
	return (-1);
}

void	keynum_release(u8 id)
{
	t_key	*key = get_key(id);

	if (key)
	{
		key->ignore = true;
		key->is_pressed = false;
	}
}

void	keynum_replace(u8 id, void (*(func))(void))
{
	t_key	*key = get_key(id);

	if (key)
		key->callback = func;
}

void	unbind_allkeys(void)
{
	s8		i = -1;

	while (++i < BUTTON_MAX)
		get_core()->key[i].callback = NULL;
}

void	unbind_keynum(u8 i)
{
	if (i < BUTTON_MAX)
		get_core()->key[i].callback = NULL;
}

bool	keynum_execute(u8 id)
{
	t_key	*key = get_key(id);

	if (key	&& !key->ignore && key->is_pressed && key->callback)
		return (key->callback(), true);
	return (false);
}

bool	key_pressed(u16 key)
{
	return (!((*(vu16 *)0x4000130) & key));
}

t_key	*get_key(u8 id)
{
	if (id < BUTTON_MAX)
		return (&get_core()->key[id]);
	return (NULL);
}
