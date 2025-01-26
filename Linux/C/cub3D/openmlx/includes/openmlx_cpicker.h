/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_cpicker.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:37:41 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 18:51:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_CPICKER_H
# define OPENMLX_CPICKER_H

typedef struct colpicker_s
{
	__uint32_t	*c_color;
	__uint32_t	new_color;
	__uint32_t	init_color;
	__uint32_t	bar_color;
	t_vec2		u;
	t_vec2		cursor;
	t_vec2		cursor_bar;
	t_vec2		grd;
	t_vec2		bar;
	t_vec2		screen;
	int			is_open;
}	t_colpicker;

//test color picker
void		cpicker_open(void);
void		cpicker_init(t_ml *lx);
void		cpicker_show(t_ml *lx, char *merge_to);
void		cpicker_grad(t_ml *lx);
void		cpicker_check_cursor(t_ml *lx, t_vec2 u);
void		cpicker_cursor_bar(char *name, t_vec2 v, __uint32_t *cl);
void		cpicker_cursor(char *name, __uint32_t c);
void		cpicker_edit(__uint32_t *c);
void		cpicker_moveto(t_vec2 v);
#endif