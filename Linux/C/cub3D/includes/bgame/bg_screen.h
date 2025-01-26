/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_screen.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:29:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/09/19 19:13:53 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_SCREEN_H
# define BG_SCREEN_H

typedef struct area_s
{
	t_vec2	a1;
	t_vec2	a2;
	t_vec2	a3;
	t_vec2	a4;
	t_vec2	u;
}	t_area;

typedef struct screen_s
{
	int		x;
	int		y;
	t_area	area;
}	t_screen;

void	bg_set_safearea(t_screen *sc);
void	bg_register_screen(void);
#endif