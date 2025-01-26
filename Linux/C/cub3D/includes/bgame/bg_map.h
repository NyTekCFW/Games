/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:25:12 by lchiva            #+#    #+#             */
/*   Updated: 2024/10/02 19:24:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_MAP_H
# define BG_MAP_H

typedef struct map_s
{
	char		**map;
	int			width;
	int			height;
	int			dimension;
	__uint32_t	color_ceil;
	__uint32_t	color_floor;
	__uint32_t	color_rgb;
}	t_map;

void	bg_map_register(void);
int		bg_isinmap(t_vec2 v);
int		bg_can_walk(t_vec2 v);
#endif