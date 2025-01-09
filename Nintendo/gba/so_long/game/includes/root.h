/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   game.h                                                                   */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 25/12/2024 19:49:21 by NyTekCFW                                 */
/*   Updated: 25/12/2024 19:49:45 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

typedef struct root_s
{
	t_submenu	submenu;
	t_gameinfo	gameinfo;
	t_gamestate	gamestate;
	t_settings	settings;
	t_trophy	trophies[TROPHY_MAX];
	t_stats		stats;
	t_save		save;
}ALIGN(4)	t_root;

t_root		*get_root(void);
t_save		*get_save(void);
t_stats		*get_stats(void);
t_submenu	*get_submenu(void);
t_settings	*get_settings(void);
t_gameinfo	*get_gameinfo(void);
t_gamestate	*get_gamestate(void);
t_trophy	*get_trophies(void);
t_trophy	*get_trophy(u8 index);
#endif
