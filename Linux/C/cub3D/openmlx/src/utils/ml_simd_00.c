/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_simd_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:47:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 06:18:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief check if the 2 pixel in entry is valid
/// @param c 2 pixel
/// @return true if the 2 pixel are correct
static int	is_val64_color(__uint64_t c)
{
	__uint32_t	upper;
	__uint32_t	lower;

	upper = (c >> 32) & 0xFFFFFFFF;
	lower = c & 0xFFFFFFFF;
	if (upper == 0 || upper == 0xFF000000)
		return (0);
	if (lower == 0 || lower == 0xFF000000)
		return (0);
	return (1);
}

/// @brief SIMD Memory Optimization for merge
/// @param dst memory destination
/// @param src memory source
/// @param n size to copy
void	smo_copy_img(void *dst, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i + sizeof(long) <= n)
	{
		if (is_val64_color(*(const __uint64_t *)(src + i)))
			*(__uint64_t *)(dst + i)
				= *(const __uint64_t *)(src + i);
		i += sizeof(long);
	}
	while (i + sizeof(int) <= n)
	{
		if (is_valid_color(*(const __uint32_t *)(src + i)))
			*(__uint32_t *)(dst + i)
				= *(const __uint32_t *)(src + i);
		i += sizeof(int);
	}
	while (i + sizeof(char) <= n)
	{
		*(__uint8_t *)(dst + i)
			= *(const __uint8_t *)(src + i);
		i += sizeof(char);
	}
}

/// @brief SIMD Memory Optimization
///for basic memory block copy
/// @param dst memory destination
/// @param src memory source
/// @param n size to copy
void	smo_copy(void *dst, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i + sizeof(long) <= n)
	{
		*(__uint64_t *)(dst + i)
			= *(const __uint64_t *)(src + i);
		i += sizeof(long);
	}
	while (i + sizeof(int) <= n)
	{
		*(__uint32_t *)(dst + i)
			= *(const __uint32_t *)(src + i);
		i += sizeof(int);
	}
	while (i + sizeof(char) <= n)
	{
		*(__uint8_t *)(dst + i)
			= *(const __uint8_t *)(src + i);
		i += sizeof(char);
	}
}

/// @brief SIMD Memory Optimization
///for basic memory block set
/// @param dst memory destination
/// @param c value in unsigned char
/// @param n size to copy
void	smo_set(void *dst, __uint8_t c, size_t n)
{
	size_t		i;

	i = 0;
	while (i + sizeof(long) <= n)
	{
		*(__uint64_t *)(dst + i) = (c & 0xFF) * 0x0101010101010101ULL;
		i += sizeof(long);
	}
	while (i + sizeof(int) <= n)
	{
		*(__uint32_t *)(dst + i) = (c & 0xFF) * 0x01010101ULL;
		i += sizeof(int);
	}
	while (i + sizeof(char) <= n)
	{
		*(__uint8_t *)(dst + i) = c;
		i += sizeof(char);
	}
}
