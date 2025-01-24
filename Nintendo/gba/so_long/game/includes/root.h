/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   root.h                                                                   */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:16:41 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

typedef struct root_s
{
	t_submenu		submenu;
	t_gameinfo		gameinfo;
	t_settings		settings;
	t_gamestate		gamestate;
	t_area_info		area_info;
	t_custom_map	custom_map[5];	
	t_trophy		trophies[TROPHY_MAX];
	t_stats			stats;
	t_user			user;
	t_sav			sav;
}ALIGN(8)	t_root;

t_root		*get_root(void);
t_sav		*get_sav(void);
t_user		*get_user(void);
t_stats		*get_stats(void);
t_submenu	*get_submenu(void);
t_settings	*get_settings(void);
t_gameinfo	*get_gameinfo(void);
t_gamestate	*get_gamestate(void);
t_area_info	*get_area_info(void);
t_trophy	*get_trophies(void);
t_trophy	*get_trophy(u8 index);
#endif
