/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:34:53 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 20:08:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/core/parsing.h"

char	*search_tex2(char *v, char *tmp, char *tmp2, int *fd)
{
	if (!tmp && !tmp2)
		return (printf("Error\nUnable to find a texture for <%s>\n", v), NULL);
	else if (tmp && tmp2)
	{
		xfree((void **)&tmp);
		xfree((void **)&tmp2);
		return (printf("Error\nMultiple %s texture found\n", v), NULL);
	}
	else if (tmp || tmp2)
	{
		if (!tmp && tmp2)
		{
			tmp = tmp2;
			tmp2 = NULL;
		}
		*fd = open(tmp, O_RDONLY);
		if (*fd > 0)
		{
			close(*fd);
			return (tmp);
		}
		printf("Error\nUnable to open <%s>.\n", tmp);
		xfree((void **)&tmp);
	}
	return (tmp);
}

void	tmp_map_clear(char **map, t_vec2 d)
{
	int	u;

	u = 0;
	if (map)
	{
		while (u < d.y)
		{
			xfree((void **)&map[u]);
			++u;
		}
	}
	xfree((void **)&map);
}
