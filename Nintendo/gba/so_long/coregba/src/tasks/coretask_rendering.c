/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coretask_rendering.c                                                     */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 19:29:02 by NyTekCFW                                 */
/*   Updated: 21/12/2024 19:29:17 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

void	run_task_rendering(t_engine *engine, t_callback *callback)
{
	static u32	left = 0;
	u32			cpu = 0;

	while (clock() < left)
		;
	left = clock() + (CLOCKS_PER_SEC / (30 * engine->timescale));
	cpu = clock();
	if (callback->rendering)
		callback->rendering();
	while (clock() < cpu + (CLOCKS_PER_SEC / engine->max_fps))
		;
	engine->fps_out = get_fps(cpu);
}
