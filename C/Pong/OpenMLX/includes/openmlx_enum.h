/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_enum.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:29:24 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 11:49:24 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_ENUM_H
# define OPENMLX_ENUM_H

typedef struct ml_s	t_ml;

enum e_ml_mode
{
	ML_MODE_FILL	= 0U,
	ML_MODE_LINE,
	ML_MODE_MAX
};

enum e_ml_texture
{
	ML_TEXTURE_NONE	= 0U,
	ML_TEXTURE_IMG,
	ML_TEXTURE_MAX
};

enum e_ml_texture_angle
{
	ML_UV_0	= 0U,
	ML_UV_90,
	ML_UV_MAX
};
enum e_ml_texture_wrapping
{
	ML_WRAP_REPEAT	= 0U,
	ML_WRAP_MIRRORED_REPEAT,
	ML_WRAP_REPEAT_CENTER,
	ML_WRAP_MAX
};

enum e_ml_primitive
{
	ML_PRIM_POINTS	= 0U,
	ML_PRIM_LINES,
	ML_PRIM_LINE_STRIP,
	ML_PRIM_LINE_LOOP,
	ML_PRIM_TRIANGLES,
	ML_PRIM_QUADS,
	ML_PRIM_QUAD_STRIP,
	ML_PRIM_POLYGON,
	ML_PRIM_MAX
};

enum e_gmlx
{
	ACT_INIT	= 0U,
	ACT_GET,
	ACT_FREE,
	ACT_MAX
};

#endif