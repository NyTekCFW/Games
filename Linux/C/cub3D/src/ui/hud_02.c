/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   hud_02.c                                                                 */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 26/01/2025 09:29:38 by NyTekCFW                                 */
/*   Updated: 26/01/2025 09:29:39 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_axis.h"

static void	ml_drawline(t_vec2 xy1, t_vec2 xy2, __uint32_t s, __uint32_t cl)
{
	t_prim	c;

	c = ml_begin(ML_PRIM_LINES);
	ml_vertex(&c, xy1);
	ml_vertex(&c, xy2);
	ml_color(&c, cl);
	ml_size(&c, s);
	ml_savemesh(&c, "framework");
	ml_end(&c);
}

__uint32_t	update_dmg_color(__uint32_t start_color, clock_t hitmarker_time)
{
	clock_t		elapsed;
	float		ratio;
	__uint8_t	rgb[3];

	elapsed = hitmarker_time - clock();
	ratio = (float)elapsed / (float)CLOCKS_PER_SEC;
	if (ratio < 0)
		ratio = 0;
	if (ratio > 1)
		ratio = 1;
	rgb[0] = (start_color >> 16) & 0xFF;
	rgb[1] = (start_color >> 8) & 0xFF;
	rgb[2] = start_color & 0xFF;
	rgb[0] = (__uint8_t)(rgb[0] * ratio);
	rgb[1] = (__uint8_t)(rgb[1] * ratio);
	rgb[2] = (__uint8_t)(rgb[2] * ratio);
	if (rgb[0] < 0x7f)
		return (0);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	hitmarker(void)
{
	t_axis	*zm;

	zm = get_zm();
	if (zm && clock() < zm->hitmarker_time)
	{
		ml_drawline((t_vec2){624, 346}, (t_vec2){635, 356}, 1, zm->dmg_color);
		ml_drawline((t_vec2){644, 356}, (t_vec2){658, 346}, 1, zm->dmg_color);
		ml_drawline((t_vec2){624, 373}, (t_vec2){635, 363}, 1, zm->dmg_color);
		ml_drawline((t_vec2){644, 363}, (t_vec2){658, 373}, 1, zm->dmg_color);
		zm->dmg_color = update_dmg_color(zm->dmg_color, zm->hitmarker_time);
	}
}

void	_health_loc(t_prim *p, t_area *ar, t_player *user, int health)
{
	t_axis	*zm;
	int		o;

	zm = get_zm();
	o = has_perk(PERK_JUGGERNOG);
	if ((zm && zm->alive) || user->health < (150 * (1 + o)))
	{
		ml_vertex(p, (t_vec2){466 + 2, 358});
		ml_vertex(p, (t_vec2){466 + 10 + health, 358});
		ml_vertex(p, (t_vec2){466 + 10 + health, 363});
		ml_vertex(p, (t_vec2){466 + 2, 363});
	}
	else
	{
		ml_vertex(p, (t_vec2){ar->a1.x + 2, ar->a4.y - 204});
		ml_vertex(p, (t_vec2){ar->a1.x + 10 + health, ar->a4.y - 204});
		ml_vertex(p, (t_vec2){ar->a1.x + 10 + health, ar->a4.y - 199});
		ml_vertex(p, (t_vec2){ar->a1.x + 2, ar->a4.y - 199});
	}
}
