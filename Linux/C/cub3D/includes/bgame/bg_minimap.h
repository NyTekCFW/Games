/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_minimap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:57:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/08 10:02:28 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_MINIMAP_H
# define BG_MINIMAP_H

void	draw_minimap(void);
void	draw_compass(void);
void	draw_arrow(t_player *player, t_vec2 pos);
void	init_minimap(int lm);
#endif