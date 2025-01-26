/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_typewritter_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:58:38 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/08 12:09:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief get width of character
/// @param c character
/// @return 
int	font_spacing(char c)
{
	if (c >= '0' && c <= '9')
		return (17);
	else if (c >= 'a' && c <= 'z')
	{
		if (c == 'w' || c == 'm' || c == 'z')
			return (21);
		else
			return (17);
	}
	else if (c == '.' || c == ',' || c == ' ')
		return (8);
	if (c == 'W' || c == 'M' || c == 'Z')
		return (24);
	return (19);
}

/// @brief get width of a string
///with font_spacing
/// @param str string
/// @return 
int	r_textwidth(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str && str[i])
	{
		w += font_spacing(str[i]);
		i++;
	}
	return (w + 15);
}

/// @brief get height of a string
int	r_textheight(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 26;
	while (str[i])
	{
		if (str[i] == '\n')
			w += 26;
		i++;
	}
	return (w);
}

/// @brief write a text into window
///with monospace_ttf fonts
/// @param dest name of the image
///where typewritter will export
/// @param str string
/// @param v position
void	typewritter(char *dest, char *str, t_vec2 v)
{
	size_t		i;
	char		m[17];
	int			c;
	t_shaders	*sh;

	i = 0;
	c = v.x;
	sh = get_img(dest);
	while (str && str[i] && sh)
	{
		if (str[i] == '\n')
		{
			v = (t_vec2){c, v.y + 26};
			i++;
			continue ;
		}
		xmemcpy(m, "\0", 17);
		if (str[i] >= '!' && str[i] <= '~')
			xmemcpy(m, "monospace_000\0", 17);
		m[11] = 0x30 + (((str[i] - 0x21) / 10) % 10);
		m[12] = 0x30 + ((str[i] - 0x21) % 10);
		merge_img(sh, get_img(m), v);
		v.x += font_spacing(str[i]);
		i++;
	}
}
