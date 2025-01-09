/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_enum.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:13:36 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/20 10:32:53 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_ENUM_H
# define SL_ENUM_H

enum e_flags
{
	p_god			= (1 << 0),
	p_speed			= (1 << 2),
	p_x2xp			= (1 << 4),
	p_info			= (1 << 6),
	p_max
};

enum e_type
{
	g_ground		= '0',
	g_wall			= '1',
	g_axis			= 'A',
	g_collect		= 'C',
	g_exit			= 'E',
	g_fire			= 'F',
	g_player		= 'P'
};

enum e_hashstr
{
	hstr_reso		= 3920062447987983UL,
	hstr_keyboard	= 304861968064750695UL
};

enum e_resolution
{
	r_error			= -1,
	r_480p,
	r_720p,
	r_1080p,
	r_1440p,
	r_2160p,
	r_max
};

enum e_keytype
{
	k_error			= -1,
	k_qwerty,
	k_azerty,
	k_max
};

enum e_keybind
{
	kb_up			= 0,
	kb_down,
	kb_left,
	kb_right,
	kb_max
};

enum e_mouse
{
	m_left_click	= 1,
	m_middle_click,
	m_right_click,
	m_scroll_up,
	m_scroll_down,
	m_button_down	= 8,
	m_button_up,
	m_max
};

enum e_game_status
{
	status_main		= (0 << 0),
	status_playing,
	status_pause,
	status_cmd,
	status_minimap,
	status_dead,
	status_max
};

enum e_frame
{
	f_fire = 0,
	f_player,
	f_melee,
	f_axis,
	f_exit,
	f_ellipse,
	f_fps,
	f_timer,
	f_sound_effect,
	f_max
};

enum e_anim
{
	a_fire,
	a_player,
	a_player_melee,
	a_axis,
	a_exit,
	a_max
};
enum e_centity
{
	c_player = 0,
	c_axis,
	c_fire,
	c_ground,
	c_wall,
	c_exit,
	c_collect,
	c_max
};
#endif