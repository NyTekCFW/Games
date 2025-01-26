/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_command_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:44:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:57:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/weapons/sp_weapons.h"
#include "../../includes/game/g_client_look.h"
#include "../../includes/game/g_client_move.h"
#include "../../includes/game/g_sound.h"

static void	pswitchweapon(void)
{
	static __uint32_t	ammo[2] = {0xFFFF, 0xFFFF};
	t_player			*p;
	char				*str;

	p = get_user();
	if (p && p->weapon && p->status == USER_ALIVE)
	{
		if (p->weapon->id == WPN_NONE)
		{
			str = "M1911";
			if (p->is_gun_pap)
				str = "SALLY";
			give_weapon(str, ammo[0], ammo[1]);
			playsound("switch", 0, 0, 1);
		}
		else
		{
			ammo[0] = p->weapon->ammo_clip;
			ammo[1] = p->weapon->ammo_stock;
			take_weapon();
		}
	}
}

static void	pflash_light(void)
{
	t_key		*key;
	t_player	*p;

	p = get_user();
	key = get_key(BUTTON_FLASHLIGHT);
	if (p && key && p->status == USER_ALIVE)
	{
		p->flashlight = !p->flashlight;
		key->ignore = 1;
		key->is_pressed = 0;
	}
}

static void	pweapfire(void)
{
	t_key			*key;
	int				id;
	t_player		*p;
	t_weapon_data	*wdata;

	p = get_user();
	key = get_key(BUTTON_FIRE);
	wdata = get_wpn_data();
	if (p && key && wdata && p->status == USER_ALIVE)
	{
		weapon_fired();
		if (p->weapon)
		{
			id = p->weapon->id;
			if (wdata[id].fire_mode
				== WPN_MODE_SINGLE_SHOT
				|| (!wdata[id].fire_mode && p->weapon
					&& p->weapon->ammo_clip == 0))
			{
				key->ignore = 1;
				key->is_pressed = 0;
			}
		}
	}
}

static void	_p_reg_commands(__uint16_t tab[])
{
	tab[BUTTON_EXIT] = XK_Escape;
	tab[BUTTON_IMGUI] = XK_p;
	add_keycode(tab[BUTTON_MOVE_FORWARD], scr_move_forward);
	add_keycode(tab[BUTTON_MOVE_BACKWARD], scr_move_backward);
	add_keycode(tab[BUTTON_MOVE_LEFT], scr_move_left);
	add_keycode(tab[BUTTON_MOVE_RIGHT], scr_move_right);
	add_keycode(tab[BUTTON_LOOK_LEFT], scr_look_left);
	add_keycode(tab[BUTTON_LOOK_RIGHT], scr_look_right);
	add_keycode(tab[BUTTON_LOOK_UP], scr_look_up);
	add_keycode(tab[BUTTON_LOOK_DOWN], scr_look_down);
	add_keycode(tab[BUTTON_FLASHLIGHT], pflash_light);
	add_keycode(tab[BUTTON_RELOAD], weapon_reload);
	add_keycode(tab[BUTTON_FIRE], pweapfire);
	add_keycode(tab[BUTTON_SWITCH], pswitchweapon);
	add_keycode(tab[BUTTON_SWITCH2], pswitchweapon);
	add_keycode(tab[BUTTON_SPRINT], NULL);
	add_keycode(tab[BUTTON_JUMP], NULL);
	add_keycode(tab[BUTTON_STANCE], NULL);
	add_keycode(tab[BUTTON_INTERACT], NULL);
	add_keycode(tab[BUTTON_EXIT], g_exit);
	add_keycode(tab[BUTTON_IMGUI], dbg_togglemenu);
}

void	p_reg_commands(void)
{
	__uint16_t	*button;

	button = get_buttons();
	if (button)
	{
		button[BUTTON_MOVE_FORWARD] = XK_w;
		button[BUTTON_MOVE_BACKWARD] = XK_s;
		button[BUTTON_MOVE_LEFT] = XK_a;
		button[BUTTON_MOVE_RIGHT] = XK_d;
		button[BUTTON_LOOK_LEFT] = XK_Left;
		button[BUTTON_LOOK_RIGHT] = XK_Right;
		button[BUTTON_LOOK_DOWN] = XK_Down;
		button[BUTTON_LOOK_UP] = XK_Up;
		button[BUTTON_SPRINT] = XK_Shift_L;
		button[BUTTON_JUMP] = XK_space;
		button[BUTTON_FLASHLIGHT] = XK_q;
		button[BUTTON_FIRE] = XK_e;
		button[BUTTON_STANCE] = XK_c;
		button[BUTTON_INTERACT] = XK_f;
		button[BUTTON_FIRE] = XK_MOUSE_LEFT_CLICK;
		button[BUTTON_RELOAD] = XK_r;
		button[BUTTON_SWITCH] = XK_MOUSE_SCROLL_DOWN;
		button[BUTTON_SWITCH2] = XK_MOUSE_SCROLL_UP;
		_p_reg_commands(button);
	}
}
