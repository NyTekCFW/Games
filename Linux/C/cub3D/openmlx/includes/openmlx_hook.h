/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_hook.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:46:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 19:30:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_HOOK_H
# define OPENMLX_HOOK_H

void	start_hook(void);
int		end_hook(t_ml *lx);
int		hook_keyboard_r(int ks, t_ml *lx);
int		hook_keyboard_p(int ks, t_ml *lx);
int		hook_mouse_p(int ks, int x, int y, t_ml *lx);
int		hook_mouse_r(int ks, int x, int y, t_ml *lx);
int		hook_mouse_m(int x, int y, t_ml *lx);
int		hook_render(t_ml *lx);

#endif