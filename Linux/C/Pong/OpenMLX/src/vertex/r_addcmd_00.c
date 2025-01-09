/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_addcmd_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:14:51 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:11:30 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

t_prim	ml_quad(t_vec2 origin, t_vec2 scale, __uint32_t color)
{
	t_prim	s;

	s = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&s, origin);
	ml_vertex(&s, (t_vec2){origin.x + scale.x, origin.y});
	ml_vertex(&s, (t_vec2){origin.x + scale.x, origin.y + scale.y});
	ml_vertex(&s, (t_vec2){origin.x, origin.y + scale.y});
	ml_color(&s, color);
	return (s);
}

t_prim	ml_triangle(t_vec2 p1, t_vec2 p2, t_vec2 p3, __uint32_t color)
{
	t_prim	s;

	s = ml_begin(ML_PRIM_TRIANGLES);
	ml_vertex(&s, p1);
	ml_vertex(&s, p2);
	ml_vertex(&s, p3);
	ml_color(&s, color);
	return (s);
}
