/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_string.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:34:12 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/22 17:57:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_STRING_H
# define OPENMLX_STRING_H

void		xwrite(int fd, const void *data, size_t n);
char		*xstrrchr(const char *s, int c);
char		*xstrcpy(char *buffer, const char *src);
int			xstrcmp(const char *s1, const char *s2);
size_t		xstrlen(const char *str);
char		*xitoa(__int64_t nbr);
char		*va_hex(__int64_t v, __int64_t base);
char		*va_float(float v, __uint32_t i);
char		*xstrchr(const char *s, int c);
char		*xstrncpy(char *dst, const char *src, size_t size);
char		*xstrstr(char *stack, const char *str);
char		*xstrdup(char *str);
char		*xstrtrim(char *str);
char		**xsplit(char const *s, char c, int *size);
__int64_t	xatoi(const char *str);
__uint32_t	fnv1a_hash(const char *str);
#endif