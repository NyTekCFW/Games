/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:08:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/16 20:54:57 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	get_file_size(int *fd, char *file)
{
	char	c;
	ssize_t	size;
	ssize_t	tsize;

	size = -1;
	tsize = 1;
	while (tsize > 0)
	{
		tsize = read(*fd, &c, 1);
		if (tsize > 0)
			size++;
	}
	close(*fd);
	*fd = open(file, O_RDONLY);
	return (size);
}

t_vec2	xopen(char *file)
{
	t_vec2	fd;

	if (!file && !*file)
		return (vec2t(-1, 0));
	fd.x = open(file, O_RDONLY);
	if (fd.x > 0)
		fd.y = get_file_size(&fd.x, file);
	return (fd);
}
