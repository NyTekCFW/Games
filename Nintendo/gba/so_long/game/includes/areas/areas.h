/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   areas.h                                                                  */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/01/2025 01:34:32 by NyTekCFW                                 */
/*   Updated: 23/01/2025 01:34:33 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREAS_H
# define AREAS_H

# include "area_01.h"

# define MAX_AREAS	1

typedef struct	areas_s
{
	const u8	*area_data;
	const u8	*area_obj_data;
	const u8	width;
	const u8	height;
	const u8	start_floor;
	const u8	max_floor;
	const u8	p_spawn_nid;
}ALIGNED(4)	t_areas;

typedef struct area_info_s
{
	u8		cur_area;
	u8		cur_floor;
	bool	is_loading_floor;//change_floor
	bool	is_initialized;
}ALIGNED(2)	t_area_info;

//Tiles data
extern const u8	tile_obj_id[256];
extern const u8	tile_area_id[256];

extern u8		_area_data[128][128];

const t_areas	*get_area(u8 id);
bool			load_area_data(u8 area_id);
void			change_area_floor(s8 n_floor);
void			start_area(u8 area_id);
#endif
