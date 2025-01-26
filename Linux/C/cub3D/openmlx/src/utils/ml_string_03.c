/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:14:50 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/22 18:49:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static int	xcountword(char const *s, char c)
{
	int	count;

	count = 0;
	while (s && *s)
	{
		if (*s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (count);
}

static int	xword_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != c)
		++i;
	return (i);
}

int	_split(const char *s, char **buffer, char c, int word)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (*s && i < word + 1)
	{
		if (*s != c)
		{
			o = xword_len(s, c);
			if (!xalloc((void **)&buffer[i], sizeof(char), o + 1))
			{
				o = 0;
				while (o < i)
					xfree((void **)&buffer[o++]);
				xfree((void **)&buffer);
				return (0);
			}
			xmemcpy(buffer[i++], s, sizeof(char) * o);
			s += o;
			continue ;
		}
		++s;
	}
	return (i);
}

char	**xsplit(char const *s, char c, int *size)
{
	char	**buffer;
	int		word;

	if (!s || !size)
		return (NULL);
	*size = 0;
	buffer = NULL;
	word = xcountword(s, c);
	if (!word)
		return (NULL);
	if (xalloc((void **)&buffer, sizeof(char *), word + 1))
		*size = _split(s, buffer, c, word);
	if (*size == 0)
		return (NULL);
	return (buffer);
}

__int64_t	xatoi(const char *str)
{
	size_t		i;
	__int64_t	mp;
	__int64_t	res;

	i = 0;
	mp = 1;
	res = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && i < 3)
		{
			res = res * 10 + str[i] - '0';
			++i;
		}
		else
			return (-1);
	}
	return (res * mp);
}
