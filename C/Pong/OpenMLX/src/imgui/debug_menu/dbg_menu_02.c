/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_menu_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:32:32 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:17:29 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static size_t	set_buffer_var(char *buffer, long var)
{
	char	*str;
	size_t	len;

	str = NULL;
	len = 0;
	str = va_hex(var, 16);
	if (str)
	{
		len = xstrlen(str);
		xstrcpy(buffer, str);
		xstrcpy(buffer + len, " / ");
		len += 3;
		xfree((void **)&str);
		str = va_hex(var, 10);
		if (str)
		{
			xstrcpy(buffer + len, str);
			len = xstrlen(buffer);
			xfree((void **)&str);
		}
	}
	return (len);
}

static void	_draw_opts_data(char **str, t_opt *opt)
{
	char	*tmp;
	size_t	len;

	len = 0;
	if (opt->_type == OPT_PTR)
		*str = va_hex((long)opt->_var, 16);
	else if (opt->_type == OPT_STR)
	{
		tmp = (char *)opt->_var;
		if (tmp && tmp[0])
		{
			len = xstrlen(tmp);
			if (xalloc((void **)str, sizeof(char), len + 1))
				xstrcpy(*str, tmp);
		}
		else if (xalloc((void **)str, sizeof(char), 6))
			xstrcpy(*str, "(null)");
	}
}

static void	draw_opts_data(t_ml *lx, t_menu *menu, t_opt *opt, int sp)
{
	char	buffer[64];
	char	*str;
	size_t	len;

	str = NULL;
	len = 0;
	xmemset(buffer, 0, sizeof(buffer));
	if (opt->_type == OPT_INT)
		len = set_buffer_var(buffer, *(int *)opt->_var);
	else if (opt->_type == OPT_LONG)
		len = set_buffer_var(buffer, *(long *)opt->_var);
	else if (opt->_type == OPT_SHORT)
		len = set_buffer_var(buffer, *(short *)opt->_var);
	else if (opt->_type == OPT_CHAR)
		len = set_buffer_var(buffer, *(char *)opt->_var);
	else if (opt->_type == OPT_FLOAT)
		str = va_float((*(float *)opt->_var), 5);
	else
		_draw_opts_data(&str, opt);
	if (len > 0)
		if (xalloc((void **)&str, sizeof(char), len + 1))
			xstrcpy(str, buffer);
	dbg_string(lx, menu->_pos.x + 300, menu->_pos.y + 35 + sp, str);
	xfree((void **)&str);
}

static void	_apply_range(t_menu *m, t_opt *opt, int s)
{
	opt->range = (t_vec4){m->_pos.x + 141,
		m->_pos.y + 28 + s, 10, 10};
	if (opt->_type != OPT_BOOL)
		opt->range.z = 148;
}

void	dbg_draw_options(t_ml *lx, t_menu *m)
{
	size_t	i;
	t_opt	*opt;
	int		s;

	i = 0;
	if (lx && m)
	{
		print_img(m->_pos, "imgui_dbg_menu");
		dbg_string(lx, m->_pos.x + 20, m->_pos.y + 15, "Debug Menu (ImGui)");
		while (i < m->_opts_count && i < 128)
		{
			opt = &m->_options[i];
			if (opt)
			{
				s = (m->_spacing * i);
				_apply_range(m, opt, s);
				dbg_string(lx, m->_pos.x + 5, m->_pos.y + 35 + s, opt->_name);
				if (opt->_var && opt->_type != OPT_BOOL)
					draw_opts_data(lx, m, opt, s);
			}
			i++;
		}
	}
}
