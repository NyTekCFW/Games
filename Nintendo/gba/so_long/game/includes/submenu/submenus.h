/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   submenus.h                                                               */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:16:20 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBMENU_H
# define SUBMENU_H

enum e_submenu
{
	SUB_MAIN_MENU		= 0,
	SUB_LVL_SELECT,
	SUB_SKIN_COLOR,
	SUB_CUSTOM_LVL,
	SUB_OPTIONS,
	SUB_CONTROLS,
	SUB_TROPHIES,
	SUB_STATS,
	SUB_RESET_STATS,
	SUB_MAX
};

typedef struct submenu_s
{
	s8		current_sub;
	s8		current_scroll;
	s8		prev_scroll[SUB_MAX];
	s8		prev_sub[SUB_MAX];
	s8		prev_count;
	void	(*entries[SUB_MAX])(void);
}ALIGNED(4)	t_submenu;

//basic submenu funcs
void	submenu_access(s8 sub);
void	submenu_set(s8 sub);
void	submenu_refresh(void);
void	submenu_back(void);
void	submenu_scroll_increment(u8 max, u8 *prev);
void	submenu_scroll_decrement(u8 max, u8 *prev);
void	render_poc(void);
//submenu callback
void	submenu_main_menu(void);
void	submenu_play(void);
void	submenu_map_custom(void);
void	submenu_skin_color(void);
void	submenu_controls(void);
void	submenu_trophies(void);
void	submenu_stats(void);
void	submenu_reset_stats(void);
void	submenu_options(void);
s16		get_scroll_in_list(u8 is_list, int scroll, int increment, int size, int display_count);
#endif