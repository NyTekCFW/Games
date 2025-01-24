/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_dobj.h                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/01/2025 03:22:35 by NyTekCFW                                 */
/*   Updated: 23/01/2025 03:22:36 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_DOBJ_H
# define BG_DOBJ_H

#define MAX_OBJECTS	256

typedef struct obj_s
{
	u16	origin;
	u8	floor;
	u8	tile_id;
	u8	state;
	u8	type;
}ALIGNED(2)	t_obj;

typedef struct dobj_s//data object
{
	t_obj	obj[MAX_OBJECTS];
	u16		obj_cnt;
	u8		obj_array[16];
	bool	obj_initialized;
	bool	obj_refresh;
}ALIGNED(4)	t_dobj;

void	precache_dobj(void);
void	remove_obj_at(u8 x, u8 y, u8 floor);
void	add_obj(u8 x, u8 y, u8 floor, t_obj object);
t_obj	*get_obj(u8 x, u8 y);
#endif