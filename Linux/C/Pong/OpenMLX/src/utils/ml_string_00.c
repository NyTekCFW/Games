/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:28:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 02:37:25 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief return a unsigned int value
///that correspond at the hash of a string,
///FNV1A hash is used for this, cause its
///simple to integrate and work correctly
/// @param str string to hash
/// @return 
__uint32_t	fnv1a_hash(const char *str)
{
	__uint32_t	hash;

	hash = 2166136261u;
	while (*str)
	{
		hash ^= (unsigned char)*str++;
		hash *= 16777619u;
	}
	return (hash);
}

/// @brief compare 2 string
/// @param s1 string 1
/// @param s2 string 2
/// @return 
int	xstrcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1++ == *s2++)
		;
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/// @brief get len of a string
/// @param str string
/// @return 
size_t	xstrlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/// @brief get the last value (c) occurance
///and return his position with a char *
/// @param s string
/// @param c value e.g : '/'
/// @return 
char	*xstrrchr(const char *s, int c)
{
	char		uc;
	const char	*last_occurrence;

	uc = (char)c;
	last_occurrence = NULL;
	while (*s != '\0')
	{
		if (*s == uc)
			last_occurrence = s;
		s++;
	}
	if (last_occurrence != NULL)
		return ((char *)last_occurrence);
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}
