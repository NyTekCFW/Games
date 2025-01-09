/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:13:40 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/07 20:51:22 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_MATH_H
# define SL_MATH_H

typedef struct vec2_s
{
	int	x;
	int	y;
}	t_vec2;

typedef struct vec2f_s
{
	float	x;
	float	y;
}	t_vec2f;

typedef struct vec3_s
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct vec4_s
{
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vec4;

//basics
int			sl_sqrt(int nb);
int			randintrange(int min, int max);
void		set_value(void *adr, __uint32_t val);
__uint32_t	get_value(void *adr);
clock_t		get_fps(clock_t cpu);
//vector
t_vec2		vec2t(int a, int b);
t_vec3		vec3t(int a, int b, int c);
t_vec4		vec4t(int a, int b, int c, int d);
//func
int			t_vec2cmp(t_vec2 c1, t_vec2 c2);
#endif