/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_client.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:27:33 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:44:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_CLIENT_H
# define BG_CLIENT_H

enum	e_perk_s
{
	PERK_NONE = 0,
	PERK_QUICKREGEN = (1 << 0),
	PERK_JUGGERNOG = (1 << 1),
	PERK_DOUBLETAP = (1 << 2),
	PERK_SPEEDCOLA = (1 << 3),
};

enum	e_status
{
	USER_DEAD	= 0,
	USER_ALIVE,
	USER_PAUSED
};

typedef struct player_s
{
	int			localclientnum;
	int			health;
	int			score;
	int			flashlight;
	int			perks;
	int			status;
	int			godmode;
	int			aimbot;
	int			is_gun_pap;
	t_vec2f		origin;
	t_vec2f		dir;
	t_vec2f		plane;
	float		vangle;
	double		speed;
	float		velocity;
	t_weapon	*weapon;
	clock_t		regentime;
	clock_t		immunity;
	clock_t		deathtime;
}	t_player;

void	bg_registerclient(void);
int		has_perk(int perk);
#endif