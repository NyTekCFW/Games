/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_anim.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:35:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/27 00:45:58 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_ANIM_H
# define BG_ANIM_H

enum e_world_anim
{
	WORLD_ANIM_MM_FIRE	= 0,
	WORLD_ANIM_FIRE,
	WORLD_ANIM_ZM
};

typedef struct anim_s
{
	int		id;
	int		max_frame;
	t_vec2	loop_anim;
	clock_t	frame_time;
	clock_t	next_frametime;
}	t_anim;

void		bg_register_world_anim(void);
void		running_env_anim(void);
t_shaders	*get_anim_img(int id, char *base_name);
#endif
