/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_math_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:13:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:10:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief apply val at the adr
/// @param adr memory address
/// @param val value in unsigned int
void	set_value(void *adr, __uint32_t val)
{
	*(__uint32_t *)adr = val;
}

/// @brief return value at adr
/// @param adr memory address
/// @return 
__uint32_t	get_value(void *adr)
{
	return (*(__uint32_t *)adr);
}

/// @brief distance between 2 position (x, y)
/// @param a position 1 in t_vec2f (x, y)
/// @param b position 2 in t_vec2f (x, y)
/// @return distance in float
float	dist(t_vec2f a, t_vec2f b)
{
	return (sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

/// @brief Check if the position 'u' is within
///a rectangular range defined by 'c' and 'd'.
///
///This function checks if the position 'u' is
///within the rectangle defined by:
/// - the top-left corner at position 'c'
/// - the size of the rectangle defined by 'd',
///where 'd.x' is the width and 'd.y' is the height
/// 
/// For example, if you call:
/// is_in_range({0, 0}, {10, 9}, {14, 15})
/// It will check if the position (10, 9) is within the
///rectangle that extends from
/// (0, 0) to (14, 15) inclusive.
///
/// @param c The top-left corner of the rectangle.
/// @param u The position to check.
/// @param d The size of the rectangle (width and height).
/// @return 1 if 'u' is inside the rectangle; 0 otherwise.
int	is_in_range(t_vec2 c, t_vec2 u, t_vec2 d)
{
	if (u.x >= c.x && u.x <= c.x + d.x
		&& u.y >= c.y && u.y <= c.y + d.y)
		return (1);
	return (0);
}
