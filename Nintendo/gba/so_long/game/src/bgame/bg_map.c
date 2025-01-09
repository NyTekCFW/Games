/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_map.c                                                                 */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 04/01/2025 03:34:18 by NyTekCFW                                 */
/*   Updated: 04/01/2025 03:34:19 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

typedef struct level_s
{
	u8	width;
	u8	height;
	u8	(*map)[];
}	t_level;

enum	e_map_category
{
	SECTION_WALLS	= 0,
	SECTION_GROUNDS,
	SECTION_COLLISIONS,
	SECTION_TRAPS,
	SECTION_ITEMS,
	SECTION_RUPPIES,
	SECTION_PLAYER
};

const u8	_wd[4]	= { 1,  2,  3,  4};//,  5,  6,  7,  8,  9, 10};
const u8	_gd[5]	= {11, 12, 13, 14, 15};//, 16, 17, 18, 19, 20};
const u8	_cd[4]	= {21, 22, 23, 24};//, 25, 26, 27, 28, 29, 30};
const u8	_td[10]	= {31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
const u8	_id[10]	= {41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
const u8	_rp[10]	= {51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
const u8	_PL		= 'P';

u8	level_a1[11][9];

s8	get_elem_category(u8 elem)
{
	if (elem >= 1 && elem <= 10)
		return (SECTION_WALLS);
	else if (elem >= 11 && elem <= 20)
		return (SECTION_GROUNDS);
	else if (elem >= 21 && elem <= 30)
		return (SECTION_COLLISIONS);
	else if (elem >= 31 && elem <= 40)
		return (SECTION_TRAPS);
	else if (elem >= 41 && elem <= 50)
		return (SECTION_ITEMS);
	else if (elem >= 51 && elem <= 60)
		return (SECTION_RUPPIES);
	else if (elem == 'P')
		return (SECTION_PLAYER);
	return (-1);
}

char	*get_level_name(u8 index)
{
	switch(index)
	{
		case 0: return ("Level A-1");
		case 1: return ("Level A-2");
		case 2: return ("Level A-3");
		case 3: return ("Level A-4");
		case 4: return ("Level B-1");
		case 5: return ("Level B-2");
		case 6: return ("Level B-3");
		case 7: return ("Level B-4");
		default: return ("N/A");
	}
	return (NULL);
}

void	**alloc_tab(u8 width, u8 height, u32 size1, u32 size2)
{
	u8		i = 0;
	void	**buf = NULL;

	if (xalloc((void **)&buf, size1, height + 1))
	{
		while (i < height)
		{
			if (!xalloc((void **)&buf[i], size2, width + 1))
			{
				while (i)
					xfree((void **)&buf[--i]);
				xfree((void **)&buf);
				return (NULL);
			}
			++i;
		}
	}
	return (buf);
}


void	build_levels(u8 *level_buffer, u8 width, u8 height, u8 lvl_id)
{
	u8	_w0 = _wd[0];
	u8	_g0 = _gd[0];
	u8	_c0 = _cd[0];
	u8	_r0 = _rp[0];
	switch (lvl_id)
	{
		case 0:
		{
			u8	tmp_lva1[11][9] =
			{
				{_w0, _w0, _w0, _w0, _w0, _w0, _w0, _w0, _w0},
				{_w0, _r0, _c0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _c0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _c0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _c0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _c0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _g0, _g0, _g0, _g0, _PL, _g0, _w0},
				{_w0, _g0, _g0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _g0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _g0, _g0, _g0, _g0, _g0, _g0, _g0, _w0},
				{_w0, _w0, _w0, _w0, _w0, _w0, _w0, _w0, _w0},
			};
			t_level xc = {0};
			xc.map = level_a1;
			break ;
		}
		case 1:
		{

			break;
		}
	}
}