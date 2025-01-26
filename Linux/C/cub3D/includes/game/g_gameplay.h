/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_gameplay.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:22:07 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 19:22:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_GAMEPLAY_H
# define G_GAMEPLAY_H

void	display(t_ml *lx);
void	run_user(void);
void	execute_keyboard(void);
void	mouse_move(int x, int y);
void	pressed_key(int ks, int x, int y, t_ml *lx);
void	display_map_loading(char *av, t_screen *sc, t_ml *lx);
#endif