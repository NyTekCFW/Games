/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_dmenu.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:06:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/10/23 23:58:00 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_DMENU_H
# define OPENMLX_DMENU_H

enum e_opts_type
{
	OPT_BOOL = 0,
	OPT_LONG,
	OPT_INT,
	OPT_FLOAT,
	OPT_DOUBLE,
	OPT_SHORT,
	OPT_CHAR,
	OPT_PTR,
	OPT_STR
};

typedef struct opts_s
{
	__uint8_t	_type;
	char		_name[25];
	double		_min;
	double		_max;
	void		*_var;
	size_t		_index;
	t_vec4		range;
}	t_opt;

typedef struct menu_s
{
	t_opt		_options[128];
	size_t		_opts_count;
	int			_open;
	t_vec2		_pos;
	int			_spacing;
	int			_width;
	int			_height;
	t_vec2		_scaling;
	__uint32_t	_color;
}	t_menu;

t_menu	*dbg_menu(int act);
void	dbg_add_slider(char *name, __uint8_t type, void *var, t_vec2f v);
void	dbg_add_bool(char *name, void *var);
void	dbg_add_ptr(char *name, void *var);
void	dbg_add_str(char *name, void *ptr_str);
void	dbg_upd_size(int w, int h);
void	dbg_string(t_ml *lx, int x, int y, char *name);
void	dbg_click(t_vec2 u);
void	dbg_draw_options(t_ml *lx, t_menu *m);
void	dbg_draw_slider(t_menu *menu, t_opt *o, size_t i);
void	dbg_display_menu(t_ml *lx);
#endif