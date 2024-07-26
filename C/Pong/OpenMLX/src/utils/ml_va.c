/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_va.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:12:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:05:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	_write_buffer(char *buffer, int begin, long count, long cast)
{
	char	*b;
	char	*e;
	size_t	len;

	b = xitoa(cast / count);
	if (b)
	{
		len = xstrlen(b);
		e = xitoa(cast % count);
		if (e)
		{
			xstrcpy(buffer + begin, b);
			xstrcpy(buffer + begin + len, ".");
			len++;
			xstrcpy(buffer + begin + len, e);
			xfree((void **)&e);
		}
		xfree((void **)&b);
	}
}

static void	convert_float(float v, __uint32_t i, char *buffer, long count)
{
	int		begin;

	begin = 0;
	i -= 1;
	while (i > 0)
	{
		count *= 10;
		i -= 1;
	}
	if (v < 0)
	{
		buffer[0] = '-';
		v *= -1;
		begin++;
	}
	_write_buffer(buffer, begin, count, (long)(v * count));
}

char	*va_float(float v, __uint32_t i)
{
	char	*buffer;
	long	count;

	count = 10;
	buffer = NULL;
	if (i == 0)
		return (xitoa((int)v));
	if (xalloc((void **)&buffer, sizeof(char), 30))
	{
		if (i < 9)
			convert_float(v, i, buffer, count);
		else
			buffer[0] = 'f';
	}
	return (buffer);
}

static void	insert_data(char *buffer, int *b, __int64_t v, __int64_t base)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (v < 0)
	{
		v *= -1;
		if (base == 16)
		{
			xstrcpy(buffer, "-0x");
			*b = 3;
		}
		else if (base == 10)
		{
			buffer[0] = '-';
			*b = 1;
		}
	}
	if (v >= base)
		insert_data(buffer, b, (v / base), base);
	buffer[(*b)++] = hex[v % base];
}

char	*va_hex(__int64_t v, __int64_t base)
{
	char	*buffer;
	int		b;

	buffer = NULL;
	b = 0;
	if (xalloc((void **)&buffer, sizeof(char), 30))
	{
		if (base == 16)
		{
			xstrcpy(buffer, "0x");
			b = 2;
		}
		insert_data(buffer, &b, v, base);
	}
	return (buffer);
}
