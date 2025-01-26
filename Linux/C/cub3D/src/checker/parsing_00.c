/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:10:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/27 01:40:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../openmlx/includes/openmlx.h"
#include "../../includes/core/parsing.h"

t_file	*get_parsing_file(int act)
{
	static t_file	*file = NULL;

	if (act == ACT_INIT && !file
		&& xalloc((void **)&file, 1, sizeof(t_file)))
		return (file);
	else if (act == ACT_GET && file)
		return (file);
	else if (act == ACT_FREE && file)
		return (xfree((void **)&file), NULL);
	return (NULL);
}

static size_t	_get_file_size(char *av)
{
	char	c;
	size_t	len;
	int		fd;

	fd = open(av, O_RDONLY);
	len = 0;
	c = 0;
	if (fd > 0)
	{
		while (read(fd, &c, 1) > 0)
			len++;
		close(fd);
	}
	return (len);
}

static void	_initdata(char *buffer)
{
	t_file	*f;

	f = get_parsing_file(ACT_INIT);
	if (f)
	{
		xmemset(f, 0, sizeof(t_file));
		f->content = buffer;
		f->pos = buffer;
	}
}

int	check_file(char *av)
{
	size_t	len;
	int		fd;
	char	*buffer;

	len = _get_file_size(av);
	fd = open(av, O_RDONLY);
	if (fd > 0)
	{
		if (len > 0)
		{
			if (xalloc((void **)&buffer, (len + 1) * sizeof(char), 1))
			{
				if (read(fd, buffer, len) > 0)
				{
					buffer[len] = '\0';
					_initdata(buffer);
					close(fd);
					return (1);
				}
				xfree((void **)&buffer);
			}
		}
		close(fd);
	}
	return (printf("Error\nCan't open %s\n", av), 0);
}

int	check_arg(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		printf("Error\n%i instead 1 arguments\n\
			Ex : ./cub3d maps/<map>.cub\n", argc - 1);
		return (0);
	}
	len = xstrlen(argv[1]);
	if (argv[1][len - 1] == 'b'
		&& argv[1][len - 2] == 'u'
		&& argv[1][len - 3] == 'c'
		&& argv[1][len - 4] == '.')
		return (1);
	printf("Error\nInvalid map format\n");
	return (0);
}
