/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:54:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/16 01:14:38 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

void	hud_render(void);
void	health_bar(t_shaders *sh);
void	display_perks(t_shaders *sh, int x, int y);
void	hitmarker(void);
void	_health_loc(t_prim *p, t_area *ar, t_player *user, int health);
#endif