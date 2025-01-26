/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:32:09 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/26 18:36:37 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

float	xfmodf(float x, float y)
{
	int	t;

	t = 0;
	if (y == 0.0f || x == 0.0f)
		return (0.0f);
	t = (int)(x / y);
	return (x - (t * y));
}

void	cycle_rainbow_color(t_vec3f *color, float speed)
{
	static float	time = 0.0f;
	float			phase;

	phase = xfmodf(time, 4.0f);
	if (phase < 1.0f)
		*color = (t_vec3f){1.0, phase, 0.0f};
	else if (phase < 2.0f)
		*color = (t_vec3f){2.0 - phase, 1.0, phase - 1.0f};
	else if (phase < 3.0f)
		*color = (t_vec3f){0.0f, 3.0 - phase, 1.0f};
	else
		*color = (t_vec3f){phase - 3.0f, 0.0f, 4.0f - phase};
	time += 0.02f * speed;
	time = xfmodf(time, 1000.0f);
}
