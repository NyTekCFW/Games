/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_string.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:34:12 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:08:14 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_STRING_H
# define OPENMLX_STRING_H

void		xwrite(int fd, const void *data, size_t n);
char		*xstrrchr(const char *s, int c);
char		*xstrcpy(char *buffer, const char *src);
int			xstrcmp(const char *s1, const char *s2);
__uint32_t	fnv1a_hash(const char *str);
size_t		xstrlen(const char *str);
char		*xitoa(__int64_t nbr);
char		*va_hex(__int64_t v, __int64_t base);
char		*va_float(float v, __uint32_t i);
#endif