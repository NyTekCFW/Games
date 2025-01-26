/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:22:15 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:22:20 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/core/parsing.h"

char	*search_textures(t_file *f, char *v, char *v1)
{
	int		fd;
	int		flag;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	flag = 0;
	if (f)
	{
		tmp = find_texture(f, v, &flag);
		if (flag == 1)
			return (NULL);
		tmp2 = find_texture(f, v1, &flag);
		if (flag == 1)
			return (NULL);
		return (search_tex2(v, tmp, tmp2, &fd));
	}
	return (tmp);
}

int	find_textures(void)
{
	t_file	*f;

	f = get_parsing_file(ACT_GET);
	if (f)
	{
		f->texture_no = search_textures(f, "NO ", "NO\t");
		f->texture_so = search_textures(f, "SO ", "SO\t");
		f->texture_we = search_textures(f, "WE ", "WE\t");
		f->texture_ea = search_textures(f, "EA ", "EA\t");
		return (f->texture_no && f->texture_so && f->texture_we
			&& f->texture_ea);
	}
	return (0);
}

__uint32_t	search_colors(char *v, char *v1)
{
	__uint32_t	c;
	__uint32_t	d;
	int			flag;

	flag = 0;
	c = check_valid_color(v, &flag);
	d = check_valid_color(v1, &flag);
	if (c != 0x80000000 && d != 0x80000000)
		return (printf("Error\nMultiple color defined for <%s>\n", v),
			0x80000000);
	else if (c == 0x80000000 && d == 0x80000000)
		return (printf("Error\nUnable to find a color for <%s>\n", v),
			0x80000000);
	else if (c == 0x80000000)
		c = d;
	return (c);
}

int	find_colors(void)
{
	t_file	*f;

	f = get_parsing_file(ACT_GET);
	if (f)
	{
		f->color[0] = search_colors("F ", "F\t");
		f->color[1] = search_colors("C ", "C\t");
		return (f->color[0] <= 0xFFFFFF && f->color[1] <= 0xFFFFFF);
	}
	return (1);
}

int	check_entry(int ac, char **av)
{
	if (check_arg(ac, av) && check_file(av[1]))
	{
		if (fill_file_map() && find_textures())
		{
			if (find_colors())
			{
				return (1);
			}
			else
				printf("Error\nInvalid Color\n");
		}
		clear_parsing();
	}
	return (0);
}
