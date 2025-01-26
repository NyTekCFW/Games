/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:43:33 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/29 23:03:57 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../openmlx/includes/openmlx.h"
#include "../../includes/core/parsing.h"

static char	*_trim_space(char *t)
{
	size_t	i;
	size_t	j;
	char	b[15];

	i = 0;
	j = 0;
	xmemset(b, 0, 15);
	while (t[i])
	{
		if (j < 13 && ((t[i] >= '0' && t[i] <= '9') || t[i] == ','))
			b[j++] = t[i];
		++i;
	}
	b[j] = 0;
	xfree((void **)&t);
	if (j >= 5 && b[0])
		return (xstrdup(b));
	return (NULL);
}

char	*find_color(t_file *file, char *v, int *flag)
{
	int		u;
	char	*p;

	if (!file || !file->content || !file->map)
		return (NULL);
	u = 0;
	while (u < file->total_line + 1 && file->map[u])
	{
		p = xstrstr(file->map[u], v);
		if (p && is_first_word(file->map[u], v, 2))
		{
			while (file->map[++u])
			{
				if (xstrstr(file->map[u], v)
					&& is_first_word(file->map[u], v, 2))
					return (printf("Error\nMultiple %s color found\n", v),
						*flag = 1, NULL);
			}
			if (line_color_check(p + xstrlen(v)))
				return (_trim_space(xstrtrim(p + xstrlen(v))));
			return (NULL);
		}
		++u;
	}
	return (NULL);
}

int	_is_valid_clr(int v[], int size, char **token)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	while (i < size)
	{
		if (token[i])
		{
			if (i < 3)
			{
				v[i] = (int)xatoi(token[i]);
				if (v[i] < 0 || v[i] > 255)
					valid = 0;
			}
			else
				valid = 0;
			xfree((void **)&token[i]);
		}
		else
			valid = 0;
		++i;
	}
	return (valid && i == 3);
}

__uint32_t	check_valid_color(char *d, int *flag)
{
	int		v[3];
	int		size;
	char	*tmp;
	char	**token;
	t_file	*f;

	xmemset(v, 0, sizeof(v));
	f = get_parsing_file(ACT_GET);
	if (f && d)
	{
		tmp = find_color(f, d, flag);
		if (tmp)
		{
			token = xsplit(tmp, ',', &size);
			xfree((void **)&tmp);
			if (token)
			{
				if (size && _is_valid_clr(v, size, token))
					return (xfree((void **)&token), ((v[0] & 0xFF) << 16
							| (v[1] & 0xFF) << 8 | (v[2] & 0xFF)));
				xfree((void **)&token);
			}
		}
	}
	return (0x80000000);
}
