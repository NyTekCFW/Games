/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_key.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:58:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 11:53:28 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_KEY_H
# define OPENMLX_KEY_H
# define XK_MOUSE_LEFT_CLICK 1
# define XK_MOUSE_RIGHT_CLICK 3
# define XK_MOUSE_SCROLL_UP 4
# define XK_MOUSE_SCROLL_DOWN 5
# define XK_MOUSE_BUTTON_9 9
# define XK_MOUSE_BUTTON_8 8

enum e_button
{
	BUTTON_FIRE	= 0,
	BUTTON_RELOAD,
	BUTTON_FLASHLIGHT,
	BUTTON_JUMP,
	BUTTON_SPRINT,
	BUTTON_STANCE,
	BUTTON_INTERACT,
	BUTTON_SWITCH,
	BUTTON_SWITCH2,
	BUTTON_LOOK_RIGHT,
	BUTTON_LOOK_LEFT,
	BUTTON_LOOK_UP,
	BUTTON_LOOK_DOWN,
	BUTTON_MOVE_FORWARD,
	BUTTON_MOVE_BACKWARD,
	BUTTON_MAX
};

typedef struct key_hook_s
{
	unsigned short	id;
	unsigned short	code;
	unsigned char	ignore;
	unsigned char	is_pressed;
	void			(*(callback))();
}	t_key;

typedef struct config_s
{
	__uint16_t	button[15];
}	t_config;

//keycode use key code e.g : XK_W ...
//keynum use the num obtained via
//get_key_num
//keycode functions are more slow
//than keynum functions
//keycode part
int			*get_key_count(void);
int			get_key_num(__uint16_t code);
int			keycode_pressed(__uint16_t code);
void		keycode_replace(__uint16_t code, void (*(func))());
void		set_keycode_status(__uint16_t code, __uint8_t active);
void		add_keycode(__uint16_t code, void (*(func))());
void		init_keyboard(t_ml *lx);
//keynum part
t_key		*get_key(__uint8_t id);
__uint16_t	*get_buttons(void);
int			keynum_execute(int num);
int			key_pressed(int num);
int			keynum_execute(int num);
void		keynum_replace(int num, void (*(func))());
#endif