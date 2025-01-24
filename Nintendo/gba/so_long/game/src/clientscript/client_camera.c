/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   client_camera.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/01/2025 19:12:32 by NyTekCFW                                 */
/*   Updated: 23/01/2025 19:12:42 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	cam_reset(s16 *cam, s16 speed)
{
	if (*cam != 0)
		*cam += (*cam > 0) ? -speed : speed;
}

void	camera_move_on_specified_tile(void)
{
	t_user	*p = get_user();

	if (p->cur_tile == 63)
	{
		if (p->dir_id < 2 && p->cam_addon[1] < 4)
			p->cam_addon[1]++;
		else if (p->dir_id >= 2 && p->dir_id < 4 && p->cam_addon[1] > -4)
			p->cam_addon[1]--;
		else if (p->dir_id >= 4)
			cam_reset(&p->cam_addon[1], 1);

		if (p->dir_id >= 4 && p->dir_id < 6 && p->cam_addon[0] < 4)
			p->cam_addon[0] += 2;
		else if (p->dir_id >= 6 && p->cam_addon[0] > -4)
			p->cam_addon[0] -= 2;
		else if (p->dir_id < 4)
			cam_reset(&p->cam_addon[0], 2);
	}
	else
	{
		cam_reset(&p->cam_addon[0], 2);
		cam_reset(&p->cam_addon[1], 1);
	}
}