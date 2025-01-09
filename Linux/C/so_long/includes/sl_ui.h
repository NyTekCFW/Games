/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_ui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:35:45 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/21 00:25:54 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_UI_H
# define SL_UI_H

typedef struct color_s
{
	__uint32_t	blue;
	__uint32_t	cyan;
	__uint32_t	green;
	__uint32_t	red;
	__uint32_t	yellow;
	__uint32_t	purple;
	__uint32_t	white;
	__uint32_t	grey;
	__uint32_t	black;
	__uint32_t	brown;
	__uint32_t	rgb;
	__uint32_t	pos;
	void		*ptr;
}	t_color;

typedef struct ui_s
{
	int			x;
	int			y;
	int			w;
	int			h;
	__uint32_t	color;
}	t_ui;

typedef struct ln_s
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	__uint32_t	color;
}	t_ln;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct uibutton_s
{
	t_ui		ui;
	int			pressed;
	char		text[32];
	void		(*call_func)();
	void		*call_param;
	int			defined;
}	t_uibutton;

typedef struct submenu_s
{
	char		title[32];
	t_uibutton	button[5];
	void		*call_param;
	int			btn_count;
	int			defined;
}	t_submenu;

t_ui	ui_add(t_vec2 xy, t_vec2 wh, __uint32_t clr);
t_ln	ln_add(t_vec2 xy1, t_vec2 xy2, __uint32_t color);
#endif