/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_gamedata.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 01/01/2025 03:54:35 by NyTekCFW                                 */
/*   Updated: 01/01/2025 03:54:38 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_GAMEDATA_H
# define BG_GAMEDATA_H

typedef struct gameinfo_s
{
	u16		coregba_version;
	u16		game_version;
}ALIGN(4)	t_gameinfo;

typedef struct gamestate_s
{
	u8		status;
	bool	in_pause;
}ALIGN(4)	t_gamestate;

#endif