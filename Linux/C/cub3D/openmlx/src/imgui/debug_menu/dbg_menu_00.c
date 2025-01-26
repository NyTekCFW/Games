/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_menu_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:50:04 by lchiva            #+#    #+#             */
/*   Updated: 2024/10/22 19:41:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

t_menu	*dbg_menu(int act)
{
	static t_menu	*menu = NULL;

	if (act == ACT_INIT && !menu)
	{
		if (xalloc((void **)&menu, sizeof(t_menu), 1))
		{
			menu->_open = 0;
			menu->_pos = (t_vec2){0};
			menu->_scaling = (t_vec2){0};
			menu->_spacing = 18;
			menu->_color = 0x294a7a;
			return (menu);
		}
	}
	else if (act == ACT_GET && menu)
		return (menu);
	else if (act == ACT_FREE && menu)
		xfree((void **)&menu);
	return (NULL);
}

void	dbg_add_slider(char *name, __uint8_t type, void *var, t_vec2f v)
{
	t_menu	*menu;
	t_opt	*opt;

	menu = dbg_menu(ACT_GET);
	if (menu && var && type >= OPT_LONG && type <= OPT_CHAR
		&& menu->_opts_count < 128)
	{
		opt = &menu->_options[menu->_opts_count];
		opt->_index = menu->_opts_count;
		opt->_type = type;
		opt->_var = var;
		opt->_max = v.y;
		opt->_min = v.x;
		xmemset(opt->_name, 0, 25);
		if (name && name[0])
		{
			if (xstrlen(name) < 25)
				xstrcpy(opt->_name, name);
			else
				xmemcpy(opt->_name, name, 25);
		}
		else
			xstrcpy(opt->_name, "(Null)");
		menu->_opts_count++;
	}
}

void	dbg_add_bool(char *name, void *var)
{
	t_menu	*menu;
	t_opt	*opt;

	menu = dbg_menu(ACT_GET);
	if (menu && var && menu->_opts_count < 128)
	{
		opt = &menu->_options[menu->_opts_count];
		opt->_index = menu->_opts_count;
		opt->_type = OPT_BOOL;
		opt->_var = var;
		xmemset(opt->_name, 0, 25);
		if (name && name[0])
		{
			if (xstrlen(name) < 25)
				xstrcpy(opt->_name, name);
			else
				xmemcpy(opt->_name, name, 25);
		}
		else
			xstrcpy(opt->_name, "(Null)");
		menu->_opts_count++;
	}
}

void	dbg_add_ptr(char *name, void *var)
{
	t_menu	*menu;
	t_opt	*opt;

	menu = dbg_menu(ACT_GET);
	if (menu && var && menu->_opts_count < 128)
	{
		opt = &menu->_options[menu->_opts_count];
		opt->_index = menu->_opts_count;
		opt->_type = OPT_PTR;
		opt->_var = var;
		xmemset(opt->_name, 0, 25);
		if (name && name[0])
		{
			if (xstrlen(name) < 25)
				xstrcpy(opt->_name, name);
			else
				xmemcpy(opt->_name, name, 25);
		}
		else
			xstrcpy(opt->_name, "(null)");
		menu->_opts_count++;
	}
}

void	dbg_add_str(char *name, void *ptr_str)
{
	t_menu	*menu;
	t_opt	*opt;

	menu = dbg_menu(ACT_GET);
	if (menu && menu->_opts_count < 128)
	{
		opt = &menu->_options[menu->_opts_count];
		opt->_index = menu->_opts_count;
		opt->_type = OPT_STR;
		opt->_var = ptr_str;
		xmemset(opt->_name, 0, 25);
		if (name && name[0])
		{
			if (xstrlen(name) < 25)
				xstrcpy(opt->_name, name);
			else
				xmemcpy(opt->_name, name, 25);
		}
		else
			xstrcpy(opt->_name, "(null)");
		menu->_opts_count++;
	}
}
