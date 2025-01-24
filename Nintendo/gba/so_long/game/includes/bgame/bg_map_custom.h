/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_map_custom.h                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:14:59 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_MAP_CUSTOM_H
# define BG_MAP_CUSTOM_H

typedef struct custom_map_s
{
	char	name[16];
	u8		*l_data;//[64 * 64];
	bool	in_use;
}ALIGN(4)	t_custom_map;

#endif