/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_map.h                                                                 */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 02/01/2025 00:13:54 by NyTekCFW                                 */
/*   Updated: 02/01/2025 00:14:25 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_MAP_H
# define BG_MAP_H

enum e_map_lvl
{
	MAP_LEVEL_A1	= 0,
	MAP_LEVEL_A2,
	MAP_LEVEL_A3,
	MAP_LEVEL_A4,
	MAP_LEVEL_B1,
	MAP_LEVEL_B2,
	MAP_LEVEL_B3,
	MAP_LEVEL_B4,
	MAP_LEVEL_MAX
};

extern const u8 area_raw_01[324];
extern const u8 area_obj_raw_01[324];
/*
extern u8	level_a1[32][32];
extern u8	level_a2[32][32];
extern u8	level_a3[32][32];
extern u8	level_a4[32][32];
extern u8	level_b1[32][32];
extern u8	level_b2[32][32];
extern u8	level_b3[32][32];
extern u8	level_b4[32][32];
*/
char	*get_level_name(u8 index);

/*
typedef struct map_lvl_s
{
	char	**map[10];
	unsigned char width;
	unsigned char height;
}	t_map_lvl;


*/
#endif