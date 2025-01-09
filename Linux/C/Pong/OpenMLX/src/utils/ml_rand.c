/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:12:18 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/22 18:10:11 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static __uint32_t	*get_seed(void)
{
	static __uint32_t	seed = 0xDEADBEEF;

	return (&seed);
}

/// @brief Seed the random number generator with the given number.
///rebuild of the function srand of stdlib.h
/// @param seed your own seed default is 0xDEADBEEF
void	xsrand(__uint32_t seed)
{
	__uint32_t	*ptr_seed;

	ptr_seed = get_seed();
	if (ptr_seed)
		*ptr_seed = seed;
}

/// @brief Return a random integer between 0 and INT MAX inclusive. 
/// @return 
int	xrand(void)
{
	__uint32_t	*ptr_seed;
	__uint64_t	n;

	ptr_seed = get_seed();
	if (ptr_seed)
	{
		n = ((0x19660D * (*ptr_seed)) + 0x3C6EF35F);
		*ptr_seed = n & 0x7FFFFFFF;
		return ((int)(*ptr_seed));
	}
	return (0);
}

/// @brief return a random number between min and max
///inclusive based on rand logic
/// @param min minimum value
/// @param max maximum value
/// @return random number between min and max
int	xrandint(int min, int max)
{
	if (max <= min)
		return (min);
	return (min + xrand() % (max - min + 1));
}
