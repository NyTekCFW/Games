/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   menu_map_custom.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:17:16 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

	/*if (p->dir_id < 4)
	{
		if (p->dir_id < 2)
			draw_sprite(52, 32, 1+ (clock() % 2), "link_melee_du");
		else
			draw_sprite(52, 32 - 12, 5+ (clock() % 2), "link_melee_du");
	}
	else
	{
		if (p->dir_id < 6)
			draw_sprite(52, 32, 1+ (clock() % 2), "link_melee_rl");
		else
			draw_sprite(52 - 12, 32, 5+ (clock() % 2), "link_melee_rl");
	}*/


void	render_poc(void)
{
	t_user			*p = get_user();
	t_area_info		*data = get_area_info();
	t_virtual		*v = get_virtual();
	t_obj			*obj = NULL;
	const t_areas	*area = get_area(data->cur_area);
	const u16		*img_data = NULL;
	int				min_tile_x = 0;
	int				min_tile_y = 0;
	int				max_tile_x = 0;
	int				max_tile_y = 0;
	int				pos = 0;
	int				raw_index = 0;
	int				y = 0;
	int				x = 0;
	u8				id = 0xFF;
	u8				val = 0;
	s16				c_y = 0;

	if (!area)
		return ;
	gcm_clear_draw_buffer();
	pos = data->cur_floor * area->height * area->width;
	p->camera.x = (p->origin.x - v->center.x);
	p->camera.y = (p->origin.y - v->center.y);
	if (!data->is_loading_floor)
		camera_move_on_specified_tile();
	p->camera.x += p->cam_addon[0];
	p->camera.y += p->cam_addon[1];
	min_tile_x = clamp(p->camera.x / 16, 0, 127) - 1;
	min_tile_y = clamp(p->camera.y / 16, 0, 127);
	max_tile_x = clamp((p->camera.x + v->scaled_width) / 16, 0, 127) + 1;
	max_tile_y = clamp((p->camera.y + v->scaled_height) / 16, 0, 127) + 1;
	c_y = (min_tile_y * 16) - p->camera.y;
	y = min_tile_y - 1;
	while (++y < max_tile_y)
	{
		x = min_tile_x;
		while (++x < max_tile_x)
		{
			val = _area_data[y][x];
			raw_index = pos + y * area->width + x;
			id = tile_area_id[val];
			if (val < 21 && val >= 1)
				img_data = img_walls;
			else if (val < 41 && val >= 21)
				img_data = img_ground;
			else if (val < 61 && val >= 41)
				img_data = img_collisions;
			else if (val < 81 && val >= 61)
				img_data = img_stairs;
			else
				img_data = NULL;
			if (id != 0xff && img_data)
				print_img((x * 16) - p->camera.x, c_y, 16, 16, id, img_data);
			if (area->area_obj_data[pos + x] > 0 || area->area_obj_data[raw_index] > 0)
			{
				obj = get_obj(x, y);
				if (obj && obj->state > 0)
					draw_sprite((x * 16) - p->camera.x, c_y, 0, "obj");
			}
		}
		pos += area->width;
		c_y += 16;
	}
	if (!data->is_loading_floor && (p->cur_tile != 61 || p->cur_tile != 62 || p->cur_tile != 64))
		draw_sprite(52 - p->cam_addon[0], 32 - p->cam_addon[1], p->dir_id + (clock() % 2), "link_walk");
}

void	submenu_map_custom(void)
{
	start_area(0);
}
