/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_math.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:51:42 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:08:31 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_MATH_H
# define OPENMLX_MATH_H

typedef struct vec2_s
{
	int	x;
	int	y;
}	t_vec2;

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

typedef struct vec2f_s
{
	double	x;
	double	y;
}	t_vec2f;

typedef struct vec3f_s
{
	double	x;
	double	y;
	double	z;
}	t_vec3f;

typedef struct vec4f_s
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4f;

void		set_value(void *adr, __uint32_t val);
__uint32_t	get_value(void *adr);
float		dist(t_vec2f a, t_vec2f b);
int			is_in_range(t_vec2 c, t_vec2 u, t_vec2 d);
void		xsrand(__uint32_t seed);
int			xrand(void);
int			xrandint(int min, int max);
int			xorrand(void);
int			xorrandint(int min, int max);
double		linear_scaling(double value, double min, double max, double w);
double		inverse_scaling(double position, double min, double max, double w);
#endif