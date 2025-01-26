/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:40:16 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/21 20:04:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

char	*xstrchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*xstrncpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src || size == 0)
		return (NULL);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*xstrstr(char *stack, const char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!*str)
		return ((char *)stack);
	len = 0;
	i = 0;
	while (str[len])
		len++;
	while (stack[i])
	{
		j = 0;
		while (str[j] && stack[i + j]
			&& stack[i + j] == str[j])
			j++;
		if (j == len)
			return (&stack[i]);
		i++;
	}
	return (NULL);
}

char	*xstrdup(char *str)
{
	char	*buffer;
	size_t	len;

	if (!str || !(*str))
		return (NULL);
	buffer = NULL;
	len = xstrlen(str);
	if (xalloc((void **)&buffer, sizeof(char), len + 1))
	{
		xmemcpy(buffer, str, len);
		buffer[len] = 0;
	}
	return (buffer);
}

char	*xstrtrim(char *str)
{
	char	*b;
	size_t	s;
	size_t	e;
	size_t	i;

	if (!str || !(*str))
		return (NULL);
	s = 0;
	i = 0;
	e = xstrlen(str) - 1;
	b = NULL;
	while (str[s] && (str[s] == ' ' || str[s] == '\t'))
		s++;
	while (e > s && (str[e] == ' ' || str[e] == '\t'))
		e--;
	if (e >= s && xalloc((void **)&b, sizeof(char), (e - s) + 2))
	{
		while (s <= e)
			b[i++] = str[s++];
		b[i] = 0;
	}
	return (b);
}
