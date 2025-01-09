/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_rand.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/12/2024 11:19:35 by NyTekCFW                                 */
/*   Updated: 20/12/2024 21:00:16 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static u32	*get_seed(void)
{
	static u32	seed = 0;

	return (&seed);
}

/// @brief Seed the random number generator with the given number.
///rebuild of the function srand of stdlib.h
/// @param seed your own seed  0 will set clock() as seed
void	xsrand(u32 seed)
{
	u32	*ptr_seed = get_seed();

	if (ptr_seed && *ptr_seed == 0)
	{
		*ptr_seed = clock();
		if (seed > 0)
			*ptr_seed = seed;
	}
}

/// @brief Return a random integer between 0 and signed INT MAX inclusive. 
/// @return 
int	xrand(void)
{
	u32	*ptr_seed = get_seed();
	u32	n = 0;

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
