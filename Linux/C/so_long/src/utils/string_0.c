/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:09:59 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/11 08:21:25 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

__uint32_t	sl_hashstr(const char *str)
{
	__uint32_t	hash;

	hash = 2784;
	while (*str++)
		hash = ((hash << 5) + hash) + (int)*str;
	return (hash);
}

int	sl_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1++ == *s2++)
		;
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	sl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*sl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[sl_strlen(s)]);
	while (*s != (unsigned char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*sl_strjoin(char *s1, char *s2)
{
	char	*buffer;
	int		sz1;
	int		sz2;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	sz1 = sl_strlen(s1);
	sz2 = sl_strlen(s2);
	buffer = (char *)malloc((sz1 + sz2 + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	sl_memcpy(buffer, s1, sz1);
	sl_memcpy(&buffer[sz1], s2, sz2);
	buffer[sz1 + sz2] = '\0';
	free(s1);
	return (buffer);
}
