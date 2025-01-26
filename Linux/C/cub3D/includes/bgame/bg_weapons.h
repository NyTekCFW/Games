/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_weapons.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:36:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/03 23:28:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_WEAPONS_H
# define BG_WEAPONS_H

enum e_weapons
{
	WPN_NONE	= 0,
	WPN_M1911,
	WPN_MAX
};

enum e_weapons_type
{
	WPN_TYPE_ERROR = -1,
	WPN_TYPE_PISTOL
};

enum e_weapons_frame
{
	WPN_FRAME_WALK	= 0,
	WPN_FRAME_AIM,
	WPN_FRAME_FIRE,
	WPN_FRAME_AIMFIRE,
	WPN_FRAME_RELOAD
};

enum e_weapons_fire_mode
{
	WPN_MODE_AUTO = 0,
	WPN_MODE_SINGLE_SHOT
};

typedef struct weapon_data_s
{
	char		name[32];
	char		o_name[32];
	int			frame[5];
	int			id;
	int			type;
	__uint32_t	debugname;
	__uint32_t	max_ammo_stock;
	__uint32_t	max_ammo_clip;
	__uint32_t	start_ammo_stock;
	__uint32_t	fire_mode;
}	t_weapon_data;

typedef struct weapon_s
{
	int			id;
	int			no_ammo;
	int			reloading;
	int			firing;
	int			last_id;
	__uint32_t	ammo_stock;
	__uint32_t	ammo_clip;
	char		info_buffer[64];
	char		anim_buffer[64];
}	t_weapon;

void	bg_register_weapondata(void);
#endif