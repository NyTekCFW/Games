/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_user.c                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/01/2025 01:15:38 by NyTekCFW                                 */
/*   Updated: 23/01/2025 01:15:39 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	bg_set_user_spawn(t_user *user)
{
	t_area_info		*data = get_area_info();
	const t_areas	*area = get_area(data->cur_area);
	s16				y = -1;
	s16				x = -1;

	if (area)
	{
		while (++y < 128)
		{
			x = -1;
			while (++x < 128)
			{
				if (_area_data[y][x] == 255)
				{
					_area_data[y][x] = area->p_spawn_nid;
					user->origin.x = (x * 16) + 8;
					user->origin.y = (y * 16) + 8;
					return ;
				}
			}
		}
	}
	user->origin.x = 8;
	user->origin.y = 8;
}

void	bg_register_user(void)
{
	t_user	*user = get_user();

	user->step = 0;
	user->flags = 0;
	user->dir_id = 0;
	user->max_health = 100;
	user->health = user->max_health;
	user->dir_flags = 0;
	user->cam_addon[0] = 0;
	user->cam_addon[1] = 0;
	user->camera = (t_vec2){0, 0};
	user->cur_tile = 0;
	bg_set_user_spawn(user);
}
