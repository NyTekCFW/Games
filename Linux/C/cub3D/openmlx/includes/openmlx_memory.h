/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_memory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:36:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/07 19:55:10 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_MEMORY_H
# define OPENMLX_MEMORY_H

void	*xmemcpy(void *dest, const void *src, size_t n);
void	*xmemset(void *s, int c, size_t n);
void	*xcalloc(size_t nmemb, size_t size);
void	xfree(void **data);
void	smo_copy(void *dst, const void *src, size_t n);
void	smo_copy_img(void *dst, const void *src, size_t n);
void	smo_set(void *dst, __uint8_t c, size_t n);
int		xalloc(void **var, size_t nmemb, size_t ts);
#endif