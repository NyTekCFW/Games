/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_settings_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:59:33 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 03:18:48 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief set a rotation of the primitive
///if a texture is defined
/// @param s current primitive
/// @param uv ML_UV_0 | ML_UV_90
void	ml_setuv(t_prim *s, int uv)
{
	if (uv < ML_UV_MAX && uv >= ML_UV_0)
		s->uv = uv;
}

/// @brief set the alignement mode 
///of the texture
/// @param s current primitive
/// @param wrap ML_WRAP_REPEAT |
/// ML_WRAP_MIRRORED_REPEAT |
/// ML_WRAP_REPEAT_CENTER
void	ml_setwrap(t_prim *s, int wrap)
{
	if (wrap < ML_WRAP_MAX && wrap >= ML_WRAP_REPEAT)
		s->wrapping = wrap;
}

/// @brief set if the render mode will
///be filled or with lines only (FDF)
/// @param s current primitive
/// @param mode e.g : ML_MODE_FILL or
///ML_MODE_LINE
void	ml_setmode(t_prim *s, int mode)
{
	if (mode < ML_MODE_MAX && mode >= ML_MODE_FILL)
		s->mode = mode;
}

/// @brief set a shader as a texture,
///that will be displayed with
///the current primitive settings
/// @param s current primitive
/// @param name name of the shaders
void	ml_settexture(t_prim *s, char *name)
{
	t_shaders	*sh;

	sh = get_img(name);
	if (sh)
	{
		s->texture = ML_TEXTURE_IMG;
		s->img = &sh->img;
		s->color_texture = 0xFFFFFF;
		s->intensity = 1.0f;
	}
}

/// @brief set a intensity if 
///a color is set on a texture
/// @param s current primitive
/// @param i intensity 0.0f->1.0f
void	ml_setintensity(t_prim *s, float i)
{
	if (i < 0.0f)
		i = 0.0f;
	else if (i > 1.0f)
		i = 1.0f;
	s->intensity = i;
}
