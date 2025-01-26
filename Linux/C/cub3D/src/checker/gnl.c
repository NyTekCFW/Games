/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:05:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/22 17:03:54 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../openmlx/includes/openmlx.h"
#include "../../includes/core/parsing.h"

static char	*_gnl_alloc(t_file *file, char *line, char *start, size_t len)
{
	if (len == 0)
	{
		if (file->pos != NULL)
		{
			if (*start == '\n')
			{
				if (xalloc((void **)&line, sizeof(char), 2))
				{
					line[0] = '\n';
					line[1] = '\0';
				}
			}
			else
				return (get_next_line(file));
		}
	}
	if (len > 0 && xalloc((void **)&line, sizeof(char), len + 1))
		xstrncpy(line, start, len + 1);
	return (line);
}

int	get_total_line(t_file *file)
{
	char	*line;

	line = NULL;
	if (file)
	{
		file->total_line = 0;
		file->pos = file->content;
		line = get_next_line(file);
		while (line && file)
		{
			++file->total_line;
			xfree((void **)&line);
			line = get_next_line(file);
		}
		file->pos = file->content;
		return (file->total_line);
	}
	return (0);
}

char	*get_next_line(t_file *file)
{
	char	*start;
	char	*nl;
	size_t	len;
	char	*line;

	if (!file || !file->pos || *(file->pos) == '\0')
		return (NULL);
	start = file->pos;
	nl = xstrchr(start, '\n');
	len = 0;
	line = NULL;
	if (nl)
	{
		len = nl - start;
		file->pos = nl + 1;
	}
	else
	{
		len = xstrlen(start);
		file->pos = NULL;
	}
	return (_gnl_alloc(file, line, start, len));
}
