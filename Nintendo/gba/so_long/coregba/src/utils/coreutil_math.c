/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_math.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:18:10 by NyTekCFW                                 */
/*   Updated: 20/12/2024 20:58:02 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

s32	sqrti(s32 num)
{
	int	res = 0;
	int	bit = 1073741824;

	if (num < 0)
		return (-1);
	while (bit > num)
		bit >>= 2;
	while (bit)
	{
		if (num >= res + bit)
		{
			num -= res + bit;
			res = (res >> 1) + bit;
		}
		else
			res >>= 1;
		bit >>= 2;
	}
	return (res);
}

float	sqrtf(float num)
{
	float	guess = 0;
	float	next_guess = 0;

	if (num < 0.0f)
		return (-1.0f);
	guess = num / 2.0f;
	while (1)
	{
		next_guess = 0.5f * (guess + num / guess);
		if (abs(next_guess - guess) < 0.00001f)
			return (next_guess);
		guess = next_guess;
	}
	return (0);
}
