/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_settings.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 01/01/2025 03:58:34 by NyTekCFW                                 */
/*   Updated: 01/01/2025 03:58:36 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_SETTINGS_H
# define BG_SETTINGS_H

enum	edvar_s
{
	VAR_SHOW_FPS		= 0,
	VAR_LIMIT_FPS
};

typedef struct settings_s
{
	bool	show_fps;
	bool	limit_fps;
}ALIGN(4)	t_settings;

char	*get_dvars_name(char *buffer, u8 index);

#endif