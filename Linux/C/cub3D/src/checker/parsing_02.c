/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:28:48 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:35:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/core/parsing.h"

void	find_map_start(t_file *file, int *start, int end, int *i)
{
	char	c;

	while (++(*start) < end && file->map[*start])
	{
		*i = -1;
		while (file->map[*start][++(*i)])
		{
			c = file->map[*start][*i];
			if (c == '\n')
			{
				*i = -2;
				break ;
			}
			else if (c == ' ' || (c >= '0' && c <= '9'))
				continue ;
			else
			{
				*i = -1;
				break ;
			}
		}
		if (*i != -1 && *i != -2)
			break ;
	}
}

void	find_map_end(t_file *file, int start, int *end, int *i)
{
	char	c;

	while (--(*end) > start && file->map[*end])
	{
		*i = -1;
		while (file->map[*end][++(*i)])
		{
			c = file->map[*end][*i];
			if (c == '\n')
			{
				*i = -2;
				break ;
			}
			else if (c == ' ' || (c >= '0' && c <= '9'))
				continue ;
			else
			{
				*i = -1;
				break ;
			}
		}
		if ((*i != -1 && *i != -2) || *i == -1)
			break ;
	}
}

int	_sym_map(char c, int *p)
{
	if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
		++(*p);
	if (!ent_is_valid(c))
		return (printf("Error\ninvalid symbol found on map!\n"), 0);
	return (1);
}

int	check_sym_map(t_file *file, int start, int end)
{
	char	c;
	int		i;
	int		p;

	p = 0;
	while (start <= end && file->map[start])
	{
		i = 0;
		while (i < file->width && file->map[start][i])
		{
			c = file->map[start][i];
			if (!_sym_map(c, &p))
				return (0);
			++i;
		}
		++start;
	}
	if (p != 1)
		return (printf("Error\nInvalid number of player spawn (%i / 1)\n", p),
			0);
	return (1);
}

int	parse_map(t_file *file)
{
	int		end;
	int		start;
	int		i;

	end = file->total_line;
	start = -1;
	i = -1;
	if (!file || !file->content || !file->map)
		return (printf("Error\ntmp file content\n"), 0);
	find_map_start(file, &start, end, &i);
	if (i == -1 || i == -2)
		return (printf("Error\nNo map start found\n"), 0);
	i = -1;
	find_map_end(file, start, &end, &i);
	if (i == -1 || i == -2)
		return (printf("Error\nNo map end found\n"), 0);
	i = start - 1;
	while (++i <= end)
		if ((int)xstrlen(file->map[i]) >= file->width)
			file->width = xstrlen(file->map[i]);
	file->height = (end + 1 - start);
	file->begin = start;
	if (file->height < 3 || file->width < 3 || end < start)
		return (printf("Error\nMap need to be 3x3 at minimum\n"), 0);
	return (check_sym_map(file, start, end));
}
