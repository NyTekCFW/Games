/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_save.h                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 25/12/2024 19:48:41 by NyTekCFW                                 */
/*   Updated: 25/12/2024 19:48:42 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_SAVE_H
# define BG_SAVE_H

typedef struct	skin_s
{
	u16	clr_jacket;
	u16	clr_skin;
	u16	clr_equipment;
}	t_skin;

typedef struct user_s
{
	bool	trophies[TROPHY_MAX];
}	t_user;

typedef struct save_s
{
	t_gameinfo	header;//header for game version detection
	t_skin		skin;
	t_user		user;
}	t_save;

#endif