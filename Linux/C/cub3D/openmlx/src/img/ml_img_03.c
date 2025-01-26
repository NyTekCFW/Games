/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:09:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 17:29:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	_set_exported_name(char *buffer, char *name)
{
	int	add;

	xmemset(buffer, 0, 128);
	add = 0;
	if (xstrlen(name) < 100)
	{
		if (name[0] == '/')
			add += 1;
		xstrcpy(buffer, EXPORT_PATH);
		xstrcpy(buffer + xstrlen(buffer), &name[add]);
		xstrcpy(buffer + xstrlen(buffer), ".ilx\0");
	}
}

/// @brief write the header and data
/// @param buffer exported file
/// @param sh image to export
static void	_export_data(char *buffer, t_shaders *sh)
{
	int			fd;
	t_shaders	tmp;

	tmp = (t_shaders){0};
	if (buffer && sh)
	{
		fd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd > 0)
		{
			xmemcpy(&tmp, sh, sizeof(t_shaders));
			tmp.next = NULL;
			tmp.is_stored = 0;
			tmp.img.ptr = NULL;
			tmp.img.addr = NULL;
			xwrite(fd, &tmp, sizeof(t_shaders));
			xwrite(fd, sh->img.addr, sh->img.size);
			close(fd);
		}
	}
}

/// @brief export a shader as
///a .bin file
/// @param name name of the 
///image to export
void	export_img(char *name)
{
	t_shaders	*sh;
	char		buffer[128];

	if (name)
	{
		sh = get_img(name);
		if (sh && xstrlen(name) < 100)
		{
			_set_exported_name(buffer, name);
			_export_data(buffer, sh);
		}
	}
}

/// @brief register an exported image <image>.ilx
/// @param name name of the exported image
///e.g : register_exp_img("color_picker_bar");
///image can be get like that :
///get_img("color_picker_bar");
void	register_exp_img(char *name)
{
	t_shaders	tmp;
	t_shaders	*sh;
	ssize_t		p;
	char		nm[128];
	int			fd;

	_set_exported_name(nm, name);
	if (!get_img(nm))
	{
		fd = open(nm, O_RDONLY, 0644);
		if (fd > 0)
		{
			p = read(fd, &tmp, sizeof(tmp));
			create_img((t_ui){tmp.img.width,
				tmp.img.height, 0}, fill_img_color, name);
			sh = get_img(name);
			if (sh)
			{
				p = read(fd, sh->img.addr, sh->img.size);
				(void)p;
			}
			close(fd);
		}
	}
}

/// @brief make a gradient between 2 color (0xRRGGBB)
///with a transition factor 0 > 1.0
/// @param sc start color
/// @param ec end color
/// @param factor transition factor 0 > 1.0
/// @return result
__uint32_t	gradient(__uint32_t sc, __uint32_t ec, float factor)
{
	__uint8_t	r1[3];
	__uint8_t	r2[3];
	__uint8_t	r3[3];

	r1[0] = (sc >> 16) & 0xFF;
	r1[1] = (sc >> 8) & 0xFF;
	r1[2] = sc & 0xFF;
	r2[0] = (ec >> 16) & 0xFF;
	r2[1] = (ec >> 8) & 0xFF;
	r2[2] = ec & 0xFF;
	r3[0] = r1[0] + (r2[0] - r1[0]) * factor;
	r3[1] = r1[1] + (r2[1] - r1[1]) * factor;
	r3[2] = r1[2] + (r2[2] - r1[2]) * factor;
	return ((r3[0] << 16) | (r3[1] << 8) | r3[2]);
}
