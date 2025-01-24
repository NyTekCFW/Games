/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_math.h                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:20:23 by NyTekCFW                                 */
/*   Updated: 20/12/2024 20:05:57 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREUTIL_MATH_H
# define COREUTIL_MATH_H

# define abs(x) ((x < 0.0f) ? -x : x)
# define min(a, b) ((a) < (b) ? (a) : (b))
# define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct vec2_s
{
	int	x;
	int	y;
}	t_vec2;
/*
typedef struct vec3_s
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct vec3f_s
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct vec4_s
{
	int	x;
	int	y;
	int	z;
}	t_vec4;
*/

s32		sqrti(s32 num);
float	sqrtf(float num);
int		clamp(int value, int min, int max);
#endif
