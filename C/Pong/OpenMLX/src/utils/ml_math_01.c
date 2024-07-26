/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_math_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:33:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:11:37 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

double	linear_scaling(double value, double min, double max, double w)
{
	return (((value - min) * w) / (max - min));
}

double	inverse_scaling(double position, double min, double max, double w)
{
	double	v;

	v = (position * (max - min) / w) + min;
	if (v >= max)
		v = max;
	else if (v <= min)
		v = min;
	return (v);
}
