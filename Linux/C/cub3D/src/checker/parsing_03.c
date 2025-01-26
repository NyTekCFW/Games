/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:57 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:32:53 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/core/parsing.h"

int	is_first_word(const char *p, const char *v, int res)
{
	int	i;
	int	a;

	if (!p || !v)
		return (0);
	while (*p == ' ' || *p == '\t')
		++p;
	i = 0;
	a = 0;
	while (v[i] && p[i] && v[i] == p[i])
	{
		++i;
		++a;
	}
	if (!v[i] && a == res)
		return (1);
	return (0);
}

char	*find_texture(t_file *file, char *v, int *flag)
{
	int		u;
	char	*p;

	if (!file || !file->content || !file->map)
		return (NULL);
	u = -1;
	while (file->map[++u])
	{
		p = xstrstr(file->map[u], v);
		if (p && is_first_word(file->map[u], v, 3))
		{
			while (file->map[++u])
			{
				if (xstrstr(file->map[u], v)
					&& is_first_word(file->map[u], v, 3))
					return (printf("Error\nMultiple %s texture found\n", v),
						*flag = 1, NULL);
			}
			return (xstrtrim(xstrstr(p, "./textures/")));
		}
	}
	return (NULL);
}
