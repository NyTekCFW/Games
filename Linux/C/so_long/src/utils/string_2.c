/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:40:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/24 05:28:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

char	*sl_strrchr(const char *s, int c)
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

void	rp_join(char *buff, char *str)
{
	size_t	s;

	s = sl_strlen(buff);
	while (*str)
	{
		buff[s] = *str;
		str++;
		s++;
	}
	buff[s] = 0;
}
