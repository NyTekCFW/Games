/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:32:34 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 05:17:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief memcpy boosted with SMO methode
/// @param dest destination
/// @param src source
/// @param n size
/// @return dest ptr
void	*xmemcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	smo_copy(dest, src, n);
	return (dest);
}

/// @brief memset boosted with SMO methode
/// @param s source
/// @param c value that will be converted
///in unsigned char
/// @param n size
/// @return s ptr
void	*xmemset(void *s, int c, size_t n)
{
	__uint8_t	ux;

	ux = (__uint8_t)c;
	smo_set(s, ux, n);
	return (s);
}

/// @brief calloc boosted with SMO method
/// @param nmemb sizeof(value type)
/// @param size size to alloc
/// @return memory allocated ptr
void	*xcalloc(size_t nmemb, size_t size)
{
	void	*mc;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (((size * nmemb) / nmemb) != size)
		return (NULL);
	mc = malloc(nmemb * size);
	if (!mc)
		return (NULL);
	xmemset(mc, 0, nmemb * size);
	return (mc);
}

/// @brief do a calloc, set the result into var and
///return true or false if alloc fail or no
/// @param var (void **)&var
/// @param nmemb sizeof(value type)
/// @param ts size to alloc
/// @return 0 or 1
int	xalloc(void **var, size_t nmemb, size_t ts)
{
	if (nmemb == 0 || ts == 0)
		return (0);
	if (((ts * nmemb) / nmemb) != ts)
		return (0);
	*var = malloc(nmemb * ts);
	if (!*var)
		return (0);
	xmemset(*var, 0, nmemb * ts);
	return (1);
}

/// @brief check if the ptr give in param is not null
///if he are defined, it will be free and set at value null
/// @param data (void **)&data
void	xfree(void **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
}
