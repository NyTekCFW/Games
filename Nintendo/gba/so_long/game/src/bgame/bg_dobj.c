/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_dobj.c                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/01/2025 03:21:37 by NyTekCFW                                 */
/*   Updated: 23/01/2025 03:21:38 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

ALIGNED(4) IN_EWRAM t_dobj	_DOBJ = { 0 };

t_obj	*get_obj(u8 x, u8 y)
{
	const t_areas	*area = NULL;
	t_area_info		*data = get_area_info();
	int				begin = 0;
	int				end = 0;

	area = get_area(data->cur_area);
	if (!_DOBJ.obj_initialized || !area || _DOBJ.obj_refresh || data->cur_floor >= area->max_floor)
		return (NULL);
	begin = (data->cur_floor > 0) ? _DOBJ.obj_array[data->cur_floor - 1] : 0;
	end = _DOBJ.obj_array[data->cur_floor];
	while (begin < end)
	{
		if (_DOBJ.obj[begin].state > 0 && _DOBJ.obj[begin].origin == ((y << 8) | x))
			return (&_DOBJ.obj[begin]);
		++begin;
	}
	return (NULL);
}

void	add_obj(u8 x, u8 y, u8 floor, t_obj object)
{
	const t_areas	*area = NULL;
	t_area_info		*data = get_area_info();
	int				i = 0;
	t_obj			tmp = { 0 };

	area = get_area(data->cur_area);
	if (!area || !_DOBJ.obj_initialized || _DOBJ.obj_cnt >= MAX_OBJECTS
		|| get_obj(x, y) || _DOBJ.obj_refresh)
		return;
	_DOBJ.obj_refresh = true;
	object.origin = ((y << 8) | x);
	object.floor = floor;
	_DOBJ.obj[_DOBJ.obj_cnt] = object;
	++_DOBJ.obj_cnt;
	for (i = _DOBJ.obj_cnt - 1; i > 0; --i)
	{
		if (_DOBJ.obj[i].floor < _DOBJ.obj[i - 1].floor
			|| (_DOBJ.obj[i].floor == _DOBJ.obj[i - 1].floor
			&& _DOBJ.obj[i].origin < _DOBJ.obj[i - 1].origin))
		{
			tmp = _DOBJ.obj[i];
			_DOBJ.obj[i] = _DOBJ.obj[i - 1];
			_DOBJ.obj[i - 1] = tmp;
		}
		else
			break ;
	}
	for (int s = 0; s <= floor && s < area->max_floor; ++s)
		_DOBJ.obj_array[s] = (s == 0) ? 0 : _DOBJ.obj_array[s - 1];
	_DOBJ.obj_array[floor + 1] = _DOBJ.obj_cnt;
	_DOBJ.obj_refresh = false;
}

void	remove_obj_at(u8 x, u8 y, u8 floor)
{
	const t_areas	*area = NULL;
	t_area_info		*data = get_area_info();
	int				i = 0;
	int				j = 0;
	int				begin = (floor > 0) ? _DOBJ.obj_array[floor] : 0;
	int				end = 0;

	area = get_area(data->cur_area);
	if (!_DOBJ.obj_initialized || !area || _DOBJ.obj_refresh || !get_obj(x,y))
		return;
	end = (floor + 1 < area->max_floor) ? _DOBJ.obj_array[floor + 1] : _DOBJ.obj_cnt;
	_DOBJ.obj_refresh = true;
	for (i = begin; i < end; ++i)
	{
		if (_DOBJ.obj[i].origin == ((y << 8) | x))
		{
			for (j = i; j < _DOBJ.obj_cnt - 1; ++j)
				_DOBJ.obj[j] = _DOBJ.obj[j + 1];
			--_DOBJ.obj_cnt;
			for (j = floor + 1; j < area->max_floor; ++j)
			{
				if (_DOBJ.obj_array[j] > 0)
					--_DOBJ.obj_array[j];
			}
			return;
		}
	}
	_DOBJ.obj_refresh = false;
}

void	precache_dobj(void)
{
	const t_areas	*area = NULL;
	t_area_info		*data = get_area_info();
	int				u = 0;
	int				x = 0;
	int				y = 0;
	int				vmax = 0;
	int				obj_cnt = 0;
	int				c_floor = 0;

	xmemset(&_DOBJ, 0, sizeof(t_dobj));
	area = get_area(data->cur_area);
	if (!area)
		return ;
	vmax = area->height * area->width * area->max_floor;
	while (u < vmax)
	{
		if (u > 0 && !(u % (area->height * area->width)))
		{
			_DOBJ.obj_array[c_floor] = obj_cnt;
			++c_floor;
		}
		if (area->area_obj_data[u] && obj_cnt < MAX_OBJECTS)
		{
			y = (u / area->width) % area->height;
			x = (u % area->width);
			_DOBJ.obj[obj_cnt] = (t_obj)
			{
				.origin = (y << 8) | x,
				.floor = c_floor,
				.tile_id = area->area_obj_data[u],
				.type = 0,
				.state = 1
			};
			++obj_cnt;
		}
		++u;
	}
	_DOBJ.obj_array[c_floor] = obj_cnt;
	_DOBJ.obj_initialized = true;
}
