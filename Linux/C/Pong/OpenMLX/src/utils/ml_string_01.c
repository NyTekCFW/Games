/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:19:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 11:38:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief strcpy boosted with SMO method
/// @param buffer dest e.g : char buffer[32];
/// @param src source e.g : "hi guys!"
/// @return 
char	*xstrcpy(char *buffer, const char *src)
{
	size_t	i;

	i = xstrlen(src);
	smo_copy(buffer, src, i + 1);
	buffer[i] = '\0';
	return (buffer);
}

/// @brief write function with error handler
/// @param fd file descriptor
/// @param data data content
/// @param n size of data content
void	xwrite(int fd, const void *data, size_t n)
{
	ssize_t	p;

	p = write(fd, data, n);
	if (p != (long)n)
		p = write(STDERR_FILENO, "write error\n", 12);
}

static __uint64_t	_get_xitoa_len(__int64_t n)
{
	__uint64_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*_xitoa(__int64_t *nbr, char *res, __uint64_t *len)
{
	res[*len] = '\0';
	if (*nbr == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (*nbr < 0)
	{
		res[0] = '-';
		*nbr *= -1;
	}
	while (*nbr)
	{
		res[--(*len)] = *nbr % 10 + '0';
		*nbr /= 10;
	}
	return (res);
}

char	*xitoa(__int64_t nbr)
{
	__uint64_t	len;
	char		*result;

	result = NULL;
	if (nbr == -2147483648L)
	{
		if (xalloc((void **)&result, sizeof(char), 12))
		{
			xstrcpy(result, "-2147483648");
			return (result);
		}
		return (NULL);
	}
	len = _get_xitoa_len(nbr);
	if (xalloc((void **)&result, sizeof(char), len + 1))
	{
		result = _xitoa(&nbr, result, &len);
		return (result);
	}
	return (NULL);
}
