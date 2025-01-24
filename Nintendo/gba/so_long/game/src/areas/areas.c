/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   areas.c                                                                  */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/01/2025 01:33:33 by NyTekCFW                                 */
/*   Updated: 23/01/2025 01:33:35 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

ALIGNED(4) IN_EWRAM u8		_area_data[128][128] = { 0 };

ALIGNED(4) const t_areas	_areas[MAX_AREAS] =
{
	[0] =
	{
		.area_data = area_raw_01,
		.area_obj_data = area_obj_raw_01,
		.width = 9,
		.height = 12,
		.start_floor = 0,
		.max_floor = 3,
		.p_spawn_nid = 22
	}
};

const t_areas	*get_area(u8 id)
{
	if (id >= MAX_AREAS)
		return (NULL);
	return (&_areas[id]);
}
/*
u8	(*get_area_data(void))[128]
{
	return (_area_data);
}*/

static void	clear_area_data(void)
{
	u8	y = 0;

	while (y < 128)
	{
		xmemset(_area_data[y], 0, sizeof(_area_data[y]));
		++y;
	}
}

bool	load_area_data(u8 area_id)
{
	const t_areas	*area = get_area(area_id);
	t_area_info		*data = get_area_info();
	t_user			*user = get_user();
	u8				y = 0;
	u8				x = 0;
	int				pos = 0;

	xmemset(data, 0, sizeof(t_area_info));
	if (!area)//invalid area
		return (false);
	pos = area->start_floor * area->height * area->width;
	while (y < 128)
	{
		xmemset(_area_data[y], 0, sizeof(_area_data[y]));
		if (y < area->height)
		{
			x = 0;
			while (x < area->width)
			{
				_area_data[y][x] = area->area_data[pos + x];
				++x;
			}
			pos += area->width;
		}
		++y;
	}
	precache_dobj();
	data->cur_area = area_id;
	data->cur_floor = area->start_floor;
	data->is_loading_floor = false;
	data->is_initialized = true;
	return (true);
}

void	change_area_floor(s8 n_floor)
{
	const t_areas	*area = NULL;
	t_area_info		*data = get_area_info();
	t_user			*user = get_user();
	t_virtual		*virtual = get_virtual();
	u8				y = 0;
	u8				x = 0;
	u8				new = 0;
	int				pos = 0;

	area = get_area(data->cur_area);
	new = data->cur_floor + n_floor;
	if (!area || data->is_loading_floor || new < 0 || new >= area->max_floor)
		return ;
	freeze_controls(true);
	keynum_release_all();
	data->is_loading_floor = true;
	get_root()->gamestate.cl_ingame = false;
	while (y < 40)
	{
		render_poc();
		if (user->cam_addon[1] > -8)
			--user->cam_addon[1];
		draw_circle(virtual->center.x, virtual->center.y, 3 * y, 0, 1);
		gcm_prepare_flip();
		sleep(0.02);
		y += 2;
	}
	clear_area_data();
	data->cur_floor = new;
	pos = new * area->height * area->width;
	y = 0;
	while (y < 128)
	{
		xmemset(_area_data[y], 0, sizeof(_area_data[y]));
		if (y < area->height)
		{
			x = 0;
			while (x < area->width)
			{
				_area_data[y][x] = area->area_data[pos + x];
				if (_area_data[y][x] == 255)
					_area_data[y][x] = area->p_spawn_nid;
				++x;
			}
			pos += area->width;
		}
		++y;
	}
	sleep(0.2);
	y = 40;
	while (y > 0)
	{
		render_poc();
		draw_circle(virtual->center.x, virtual->center.y, 3 * y, 0, 1);
		gcm_prepare_flip();
		sleep(0.02);
		y -= 2;
	}
	user->dir_id = 0xff;
	data->is_loading_floor = false;
	get_gamestate()->cl_ingame = true;
	freeze_controls(false);
}

void	unload_area(void)
{
	t_root	*root = get_root();

	freeze_controls(true);
	root->gamestate.cl_ingame = false;
	keynum_release_all();
	clear_area_data();
}

void	start_area(u8 area_id)
{
	t_engine		*engine = get_engine();
	t_gamestate		*gstate = get_gamestate();

	gstate->cl_ingame = false;
	freeze_controls(true);
	unbind_allkeys();
	keynum_release_all();
	gcm_set_clear_color(0x01);
	gcm_clear_draw_buffer();
	gcm_prepare_flip();
	stop_sfx("snd_main_menu");
	engine->key_input_speed = 2;
	if (!load_area_data(area_id))
	{
		engine->key_input_speed = 10;
		gcm_set_clear_color(0x3def);
		gcm_clear_draw_buffer();
		gcm_prepare_flip();
		play_sfx("snd_main_menu");
		submenu_set(SUB_MAIN_MENU);
		freeze_controls(false);
		return ;
		//Error loading map
	}
	bg_register_user();
	pcommand_ingame();
	play_sfx("snd_dungeon");
	freeze_controls(false);
	gstate->cl_ingame = true;
}
