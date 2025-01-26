/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_client_script.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:32:08 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:37:36 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/bgame/bg_register_trigger.h"

int	scr_purchase(char new_id, char *current, int price, char *sound)
{
	t_player	*user;
	t_key		*key;
	int			i;

	user = get_user();
	key = get_key(BUTTON_INTERACT);
	i = 0;
	if (user && key && key_pressed(key->id))
	{
		if (user->score >= price)
		{
			user->score -= price;
			playsound("buying_sound", 0, 0, 1);
			if (sound)
				playsound(sound, 0, 0, 1);
			if (new_id && current)
				*current = new_id;
			i = 1;
		}
		else
			playsound("buying_denied", 0, 0, 1);
		key->ignore = 1;
		key->is_pressed = 0;
	}
	return (i);
}

void	scr_trigger_door(char *c)
{
	char	*str;
	char	nid;

	str = "Open door [F] [Cost:$500]";
	nid = 'T';
	if (*c == 'T')
	{
		str = "Close door [F] [Cost:$500]";
		nid = 'K';
	}
	typewritter("framework", str, (t_vec2){480, 650});
	scr_purchase(nid, c, 500, "door_open");
}

void	scr_trigger_ammo(t_player *user, int *dis)
{
	char	*s;

	s = "Buy ammo [F] [Cost:$250]";
	if (user->weapon->id == WPN_M1911
		&& can_get_ammo())
	{
		*dis = 1;
		typewritter("framework", s, (t_vec2){640 - (r_textwidth(s) / 2), 650});
		if (scr_purchase(0, NULL, 250, "switch"))
			give_max_ammo();
	}
}

void	scr_trigger_proximity(t_vec2 u, char **map, int *dis)
{
	char		c;
	t_player	*user;

	user = get_user();
	if (user && map && map[u.y])
	{
		c = map[u.y][u.x];
		if (!(*dis) && (c == 'K' || c == 'T'))
			scr_trigger_door(&map[u.y][u.x]);
		else if ((c == '[' || c == ']' || c == '{' || c == '}') && !(*dis))
			scr_trigger_perks(user, c, dis);
		else if (c == '+' && !(*dis))
			scr_trigger_ammo(user, dis);
		else if (c == 'P' && !(*dis))
			scr_trigger_pap(user, dis);
	}
}

void	scr_find_trigger_active(void)
{
	size_t		i;
	t_player	*user;
	t_trigger	*trig;
	t_map		*data;
	int			dis;

	trig = get_trigger(ACT_GET);
	data = get_map();
	user = get_user();
	i = 0;
	if (user && trig && data && data->map)
	{
		dis = 0;
		while (i < trig->size)
		{
			if (trig->ents && is_trigger_active(user, &trig->ents[i]))
				scr_trigger_proximity(trig->ents[i].pos, data->map, &dis);
			++i;
		}
	}
}
