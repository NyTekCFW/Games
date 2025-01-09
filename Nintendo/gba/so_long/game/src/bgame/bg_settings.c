/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_settings.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 02/01/2025 02:47:20 by NyTekCFW                                 */
/*   Updated: 02/01/2025 02:47:22 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char	*get_dvars_name(char *buffer, u8 index)
{
	char		*data = STR_ICON_UNCHECKED;
	t_settings	*settings = get_settings();

	switch (index)
	{
		case VAR_SHOW_FPS:
		{
			xstrcpy(buffer, "Show FPS ");
			if (settings->show_fps)
				data = STR_ICON_CHECKED;
			break ;
		}
		case VAR_LIMIT_FPS:
		{
			xstrcpy(buffer, "Limit FPS ");
			if (settings->limit_fps)
				data = STR_ICON_CHECKED;
			break ;
		}
		default:
		{
			return (xstrcpy(buffer, "N/A"));
		}
	}
	xstrcpy(&buffer[xstrlen(buffer)], data);
	return (buffer);
}
