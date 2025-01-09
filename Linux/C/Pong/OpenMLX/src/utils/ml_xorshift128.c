/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_xorshift128.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:50:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/22 18:06:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static __uint32_t	*get_seed(void)
{
	static __uint32_t	seed[4] = {123456789, 362436069, 521288629, 88675123};

	return (seed);
}

/// @brief return a random number based on xorshift128 logic
/// @return random number between INT_MIN and INT_MAX
int	xorrand(void)
{
	__uint32_t	t;
	__uint32_t	s;
	__uint32_t	*ptr_seed;

	ptr_seed = get_seed();
	if (ptr_seed)
	{
		t = ptr_seed[3];
		s = ptr_seed[0];
		ptr_seed[3] = ptr_seed[2];
		ptr_seed[2] = ptr_seed[1];
		ptr_seed[1] = s;
		t ^= t << 11;
		t ^= t >> 8;
		ptr_seed[0] = t ^ s ^ (s >> 19);
		return ((int)(ptr_seed[0] & 0x7FFFFFFF));
	}
	return (0);
}

/// @brief return a random number based on xorshift128 logic
///between min and max inclusive
/// @param min minimum value
/// @param max maximum value
/// @return random number between min and max
int	xorrandint(int min, int max)
{
	__uint32_t	rng;
	int			val;

	if (max <= min)
		return (min);
	rng = (__uint32_t)(max - min + 1);
	val = xorrand() % rng;
	return (min + val);
}
