/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_client.h                                                              */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 25/12/2024 19:39:18 by NyTekCFW                                 */
/*   Updated: 25/12/2024 19:41:21 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_USER_H
# define BG_USER_H

enum e_user_move
{
	USER_DIR_MOVE_DOWN	= (1 << 0),
	USER_DIR_MOVE_UP	= (1 << 1),
	USER_DIR_MOVE_LEFT	= (1 << 2),
	USER_DIR_MOVE_RIGHT	= (1 << 3),
};

enum e_user_flag
{
	USER_FLAGS_SPRINT		= (1 << 0),
	USER_FLAGS_MELEEING		= (1 << 1),
	USER_FLAGS_BLINKING		= (1 << 2),
	USER_FLAGS_INVISIBLE	= (1 << 3),
	USER_FLAGS_INVINCIBLE	= (1 << 4),
	USER_FLAGS_IN_CINEMATIC	= (1 << 5),
};

typedef struct user_s
{
	//direction
	u8		dir_id;
	u32		dir_flags;
	//health
	s16		health;
	s16		max_health;
	//origin
	t_vec2	origin;
	//camera
	t_vec2	camera;
	s16		cam_addon[2];
	//other data
	u32		flags;
	u32		step;
	u8		cur_tile;
}	t_user;

void	bg_register_user(void);

#endif