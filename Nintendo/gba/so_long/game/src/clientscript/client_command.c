/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   client_command.c                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 26/12/2024 23:07:56 by NyTekCFW                                 */
/*   Updated: 26/12/2024 23:07:57 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	back_menu(void)
{
	get_gamestate()->cl_ingame = false;
	stop_sfx("snd_dungeon");
	unbind_allkeys();
	get_engine()->key_input_speed = 10;
	play_sfx("snd_main_menu");
	submenu_back();
}

static void	set_fdir(u32 flag, u8 dir)
{
	t_user	*p = get_user();

	if (p->dir_id == 0xff)
		p->dir_flags = 0;
	else
		p->dir_flags |= flag;
	p->dir_id = (p->dir_id == 0xff) ? 0 : dir;
}


static bool	check_tile_task(u8 tile)
{
	if (tile == 61 || tile == 62 || tile == 64)
		return (change_area_floor(((tile == 62 || tile == 64) ? 1 : -1)), false);
	return (true);
}

static void	move_up(void)
{
	t_user	*p = get_user();
	int		y = p->origin.y + -2;
	int		px[3] = { p->origin.x / 16, (p->origin.x - 7) / 16, (p->origin.x + 7) / 16 };
	int		py = y / 16;
	int		i = 0;
	bool	can_move = true;

	p->dir_flags &= ~USER_DIR_MOVE_DOWN;
	if ((p->dir_flags & USER_DIR_MOVE_UP) && py >= 0 && py < 128)
	{
		for (i = 0; i < 3; i++)
		{
			if (px[i] < 0 || px[i] >= 128 || _area_data[py][px[i]] < 21)
			{
				can_move = false;
				break  ;
			}
		}
		if (can_move && check_tile_task(_area_data[py][px[0]]))
		{
			p->cur_tile = _area_data[py][px[0]];
			p->origin.y = y;
		}
	}
	set_fdir(USER_DIR_MOVE_UP, 2);
}

static void	move_down(void)
{
	t_user	*p = get_user();
	int		y = p->origin.y + 2;
	int		px[3] = { p->origin.x / 16, (p->origin.x - 7) / 16, (p->origin.x + 7) / 16 };
	int		py = (y + 7) / 16;
	int		i = 0;
	bool	can_move = true;

	p->dir_flags &= ~USER_DIR_MOVE_UP;
	if ((p->dir_flags & USER_DIR_MOVE_DOWN) && py >= 0 && py < 128)
	{
		for (i = 0; i < 3; i++)
		{
			if (px[i] < 0 || px[i] >= 128 || _area_data[py][px[i]] < 21)
			{
				can_move = false;
				break  ;
			}
		}
		if (can_move && check_tile_task(_area_data[py][px[0]]))
		{
			p->cur_tile = _area_data[py][px[0]];
			p->origin.y = y;
		}
	}
	set_fdir(USER_DIR_MOVE_DOWN, 0);
}

static void	move_left(void)
{
	t_user	*p = get_user();
	int		x = p->origin.x - 2;
	int		px = (x - 7) / 16;
	int		py[2] = { p->origin.y / 16, (p->origin.y + 7) / 16 };
	int		i = 0;
	bool	can_move = true;

	p->dir_flags &= ~USER_DIR_MOVE_RIGHT;
	if ((p->dir_flags & USER_DIR_MOVE_LEFT) && px >= 0 && px < 128)
	{
		for (i = 0; i < 2; i++)
		{
			if (py[i] < 0 || py[i] >= 128 || _area_data[py[i]][px] < 21)
			{
				can_move = false;
				break;
			}
		}
		if (can_move && check_tile_task(_area_data[py[0]][px]))
		{
			p->cur_tile = _area_data[py[0]][px];
			p->origin.x = x;
		}
	}
	set_fdir(USER_DIR_MOVE_LEFT, 6);
}

static void	move_right(void)
{
	t_user	*p = get_user();
	int		x = p->origin.x + 2;
	int		px = ((x + 7) / 16);
	int		py[2] = { p->origin.y / 16, (p->origin.y + 7) / 16 };
	int		i = 0;
	bool	can_move = true;

	p->dir_flags &= ~USER_DIR_MOVE_LEFT;
	if ((p->dir_flags & USER_DIR_MOVE_RIGHT) && px >= 0 && px < 128)
	{
		for (i = 0; i < 2; i++)
		{
			if (py[i] < 0 || py[i] >= 128 || _area_data[py[i]][px] < 21)
			{
				can_move = false;
				break;
			}
		}
		if (can_move && check_tile_task(_area_data[py[0]][px]))
		{
			p->cur_tile = _area_data[py[0]][px];
			p->origin.x = x;
		}
	}
	set_fdir(USER_DIR_MOVE_RIGHT, 4);
}

void	pcommand_ingame(void)
{
	keynum_replace(BUTTON_MOVE_FORWARD, move_up);
	keynum_replace(BUTTON_MOVE_BACKWARD, move_down);
	keynum_replace(BUTTON_MOVE_LEFT, move_left);
	keynum_replace(BUTTON_MOVE_RIGHT, move_right);
	keynum_replace(BUTTON_B, back_menu);
}
