/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_client_script2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:01:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 09:11:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_client_script.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/bgame/bg_register_trigger.h"

char	*get_ammo_string(t_weapon *wpn, t_weapon_data *wpns)
{
	char	*s;

	s = NULL;
	if (wpn->no_ammo)
		s = "No Ammo";
	else if (wpn->ammo_clip < (wpns[WPN_M1911].max_ammo_clip / 2) - 1
		|| !wpn->ammo_stock)
	{
		if (wpn->ammo_stock > 0)
			s = "[R] Reload";
		else
			s = "Low Ammo";
	}
	return (s);
}

void	scr_ammo_tracker(void)
{
	t_player		*user;
	t_weapon		*wpn;
	t_weapon_data	*wpns;
	char			*s;

	user = get_user();
	wpns = get_wpn_data();
	s = NULL;
	if (user && wpns)
	{
		wpn = user->weapon;
		if (wpn && wpn->id == WPN_M1911)
		{
			s = get_ammo_string(wpn, wpns);
			typewritter("framework", s,
				(t_vec2){640 - (r_textwidth(s) / 2), 580});
		}
	}
}

int	scr_get_perk_info(char c, char *str, char *j, int *f)
{
	xstrcpy(str, "Buy Quick Regen [F] [Cost:$1000]");
	xstrcpy(j, "quick_regen_jingle");
	if (c == '[')
	{
		xstrcpy(str, "Buy Juggernog [F] [Cost:$2500]");
		xstrcpy(j, "juggernog_jingle");
		*f = PERK_JUGGERNOG;
		return (2500);
	}
	else if (c == ']')
	{
		xstrcpy(str, "Buy Double Tap [F] [Cost:$2000]");
		xstrcpy(j, "double_tap_jingle");
		*f = PERK_DOUBLETAP;
		return (2000);
	}
	else if (c == '{')
	{
		xstrcpy(str, "Buy Sleight of Hand [F] [Cost:$3000]");
		xstrcpy(j, "speed_cola_jingle");
		*f = PERK_SPEEDCOLA;
		return (3000);
	}
	return (1000);
}

void	scr_trigger_perks(t_player *user, char c, int *dis)
{
	char	s[38];
	char	jingle[20];
	int		flag;
	int		price;

	xmemset(s, 0, sizeof(s));
	xmemset(jingle, 0, sizeof(jingle));
	flag = PERK_QUICKREGEN;
	price = scr_get_perk_info(c, s, jingle, &flag);
	if (!(user->perks & flag))
	{
		*dis = 1;
		typewritter("framework", s, (t_vec2){640 - (r_textwidth(s) / 2), 650});
		if (scr_purchase(0, NULL, price, jingle))
			user->perks |= flag;
	}
}

void	dodamage(t_player *user, int c, int dmg)
{
	static int	s = 0;

	if (!user->godmode && user->health > 0
		&& user->status == USER_ALIVE && clock() >= user->immunity)
	{
		user->immunity = clock() + 333333;
		user->health -= dmg;
		user->regentime = clock() + (3500000 / (1 + has_perk(PERK_QUICKREGEN)));
		if (c == 'D' && s < 15 && ++s == 15)
			playsound("easter_egg", 0, 0, 0);
		if (user->health <= 0)
		{
			user->status = USER_DEAD;
			user->health = 0;
			playsound("game_over", 0, 1, 0);
			user->deathtime = clock() + 41000000;
		}
	}
}
