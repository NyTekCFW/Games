/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_register.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:36:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/09/19 17:53:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_REGISTER_H
# define BG_REGISTER_H

t_dvars	register_double(const char *name, double value, t_vec2f limit);
t_dvars	register_int(const char *name, int value, t_vec2 limit);
t_dvars	register_color(const char *name, __uint32_t color);
t_dvars	register_boolean(const char *name, int status);
#endif
