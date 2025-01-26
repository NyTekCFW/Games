/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:56 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 20:07:45 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../openmlx/includes/openmlx.h"
#include "../../includes/core/parsing.h"

void	remove_space(char **map, t_vec2 d)
{
	t_vec2	u;

	u = (t_vec2){0, 0};
	while (u.y < d.y)
	{
		u.x = 0;
		while (u.x < d.x)
		{
			if (map[u.y][u.x] == ' ')
				map[u.y][u.x] = '1';
			else if (map[u.y][u.x] != '1'
				&& map[u.y][u.x] != '\n' && map[u.y][u.x] != 0)
				map[u.y][u.x] = '0';
			++u.x;
		}
		++u.y;
	}
}

char	**tmp_map(int act)
{
	static char	**map = NULL;
	int			i;
	size_t		len;
	t_file		*f;

	i = 0;
	f = get_parsing_file(ACT_GET);
	if (f && !map && act == ACT_INIT)
	{
		if (xalloc((void **)&map, sizeof(char *), f->height + 1))
		{
			while (i < f->height)
			{
				if (xalloc((void **)&map[i], sizeof(char), f->width + 1))
				{
					len = xstrlen(f->map[f->begin + i]);
					xmemcpy(map[i], f->map[f->begin + i], sizeof(char) * len);
					++i;
				}
			}
		}
	}
	return (map);
}

int	check_map(t_vec2 d)
{
	char	**map;

	map = tmp_map(ACT_INIT);
	if (!map)
		return (printf("Error\ntmp map failed\n"), 0);
	remove_space(map, d);
	return (floor_test(map, d));
}

static int	_check_alloc(t_file *file, int *i)
{
	int	a;

	a = 0;
	if (file && file->map)
	{
		while (a < *i + 1)
		{
			if (!file->map[a])
			{
				a = *i + 1;
				while (--a >= 0)
					xfree((void **)&file->map[a]);
				xfree((void **)&file->map);
				*i = file->total_line + 1;
				return (0);
			}
			++a;
		}
		return (1);
	}
	return (0);
}

int	fill_file_map(void)
{
	int		i;
	t_file	*file;

	file = get_parsing_file(ACT_GET);
	if (file && file->content)
	{
		i = -1;
		file->total_line = get_total_line(file);
		file->pos = file->content;
		if (xalloc((void **)&file->map, sizeof(char *), file->total_line + 1))
		{
			while (++i < file->total_line)
			{
				file->map[i] = get_next_line(file);
				if (!_check_alloc(file, &i))
					return (0);
			}
			file->width = 0;
			if (parse_map(file))
				return (check_map((t_vec2){file->width, file->height}));
		}
	}
	return (0);
}
