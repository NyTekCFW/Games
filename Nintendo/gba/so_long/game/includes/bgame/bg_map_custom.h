/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_map_custom.h                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 01/01/2025 05:08:46 by NyTekCFW                                 */
/*   Updated: 02/01/2025 02:37:18 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_MAP_CUSTOM_H
# define BG_MAP_CUSTOM_H

typedef struct build_map_s
{
	char			name[12];
	bool			in_use;
	unsigned char	data[32 * 32];
}ALIGN(4)	t_build_map;

#endif