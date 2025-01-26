/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_typewritter_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:34:19 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/08 15:45:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	set_img_color(t_shaders *sh, __uint32_t clr)
{
	__uint32_t	i;
	__uint32_t	b;
	__uint32_t	n;
	void		*adr;

	i = 0;
	if (!sh)
		return ;
	adr = (void *)sh->img.addr;
	n = sh->img.size;
	while (i + sizeof(int) <= n)
	{
		b = *(__uint32_t *)(adr + i);
		if (is_valid_color(b) && b != 0x030303)
			*(__uint32_t *)(adr + i) = clr;
		i += sizeof(int);
	}
}

static void	remove_img(t_shaders *s)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && lx->ptr && s->img.ptr)
	{
		mlx_destroy_image(lx->ptr, s->img.ptr);
		xmemset(s, 0, sizeof(t_shaders));
	}
}

static int	make_img(t_shaders *box, t_ui ui, char *name)
{
	t_ml		*lx;

	lx = gmlx(ACT_GET);
	if (lx && get_img(name) == NULL)
	{
		xmemset(box, 0, sizeof(t_shaders));
		box->file = fnv1a_hash(name);
		xstrcpy(box->img_name, name);
		box->img.height = ui.h;
		box->img.width = ui.w;
		box->next = NULL;
		box->img.ptr = mlx_new_image(lx->ptr, ui.w, ui.h);
		if (!box->img.ptr)
			return (0);
		box->img.addr = mlx_get_data_addr(box->img.ptr,
				&box->img.bpp, &box->img.len, &box->img.endian);
		box->img.size = box->img.height * box->img.len
			+ box->img.width * (box->img.bpp / 8);
		return (1);
	}
	return (0);
}

static void	print_color(t_shaders *s, t_shaders *let, t_vec2 v, __uint32_t clr)
{
	t_shaders	tmp;

	if (s && let)
	{
		if (clr == 0x030303 || !is_valid_color(clr) || clr == 0xFFFFFF)
			merge_img(s, let, v);
		else
		{
			if (make_img(&tmp, (t_ui){let->img.width, let->img.height, 0},
				"c_buffer"))
			{
				merge_img(&tmp, let, (t_vec2){0, 0});
				set_img_color(&tmp, clr);
				merge_img(s, &tmp, v);
				remove_img(&tmp);
			}
		}
	}
}

/// @brief write a text with monospace_ttf 
///fonts and a specified color
/// @param str string
/// @param v position
/// @param clr color of text
void	ctypewritter(char *dest, char *str, t_vec2 v, __uint32_t clr)
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
		print_color(sh, get_img(m), v, clr);
		v.x += font_spacing(str[i]);
		i++;
	}
}
