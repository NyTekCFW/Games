/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:14:18 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/16 08:50:49 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_vec2	vec2t(int a, int b)
{
	t_vec2	v2new;

	v2new.x = a;
	v2new.y = b;
	return (v2new);
}

t_vec3	vec3t(int a, int b, int c)
{
	t_vec3	v3new;

	v3new.x = a;
	v3new.y = b;
	v3new.z = c;
	return (v3new);
}

t_vec4	vec4t(int a, int b, int c, int d)
{
	t_vec4	v4new;

	v4new.x = a;
	v4new.y = b;
	v4new.z = c;
	v4new.w = d;
	return (v4new);
}

int	t_vec2cmp(t_vec2 c1, t_vec2 c2)
{
	if (c2.x == c1.x && c2.y == c1.y)
		return (0);
	return (1);
}
