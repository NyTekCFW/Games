/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_window_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:56:41 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 04:54:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/openmlx.h"

/// @brief create 255 pixel shaders
void	_ml_set_win_data_pixel(void)
{
	int		i;
	char	buffer[13];

	i = 0;
	return ;
	while (i < 255)
	{
		xstrcpy(buffer, "ui_pixel_000");
		buffer[9] = 0x30 + (i / 100);
		buffer[10] = 0x30 + ((i / 10) % 10);
		buffer[11] = 0x30 + (i % 10);
		buffer[12] = 0;
		create_img((t_ui){1, 1, 0x000000},
			fill_img_color, buffer);
		i++;
	}
}

/// @brief change color of the purge image
/// @param color color to apply
void	_ml_set_purge_color(__uint32_t color)
{
	t_ml		*lx;
	t_shaders	*sh;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		sh = get_img("clear_window");
		if (sh)
		{
			lx->purge_color = color;
			fill_img_color(&sh->img, lx->purge_color);
		}
	}
}
