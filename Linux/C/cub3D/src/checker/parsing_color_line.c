/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:26:12 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/27 04:26:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../openmlx/includes/openmlx.h"
#include "../../includes/core/parsing.h"

static int	check_00(int in_num, const char *n, const char **s)
{
	if (in_num)
	{
		while (n && *n && (*n == ' ' || *n == '\t'))
			++n;
		if (n && *n && *n >= '0' && *n <= '9')
			return (0);
	}
	++(*s);
	return (1);
}

static int	check_01(int *in_num, int *c_com)
{
	if (!(*in_num))
		return (0);
	*in_num = 0;
	++(*c_com);
	return (1);
}

static int	check_02(const char *s, int *in_num, int *c_com, int *c_num)
{
	if (s && *s && *s == ',')
	{
		if (!check_01(in_num, c_com))
			return (0);
	}
	else if (s && *s && *s >= '0' && *s <= '9')
	{
		if (!(*in_num))
		{
			*in_num = 1;
			++(*c_num);
		}
	}
	else
		return (0);
	return (1);
}

int	line_color_check(const char *s)
{
	int			c_num;
	int			in_num;
	int			c_com;

	c_num = 0;
	in_num = 0;
	c_com = 0;
	while (s && *s)
	{
		if (*s == ' ' || *s == '\t')
		{
			if (!check_00(in_num, s + 1, &s))
				return (0);
			continue ;
		}
		if (!check_02(s, &in_num, &c_com, &c_num))
			return (0);
		++s;
	}
	return (c_num == 3 && c_com == 2 && in_num);
}
