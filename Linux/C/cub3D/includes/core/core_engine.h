/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:20:45 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/19 19:45:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_ENGINE_H
# define CORE_ENGINE_H

void			init_imgui(void);
void			dbg_togglemenu(void);
t_screen		*get_screen(void);
t_vars			*get_var(void);
t_player		*get_user(void);
t_map			*get_map(void);
t_shaders		*get_tex(int tex);
t_weapon_data	*get_wpn_data(void);
t_shaders		**get_textures(void);
t_anim			*get_wanim(int id);
#endif