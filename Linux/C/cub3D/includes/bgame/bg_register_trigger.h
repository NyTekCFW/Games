/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_register_trigger.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:54:12 by lchiva            #+#    #+#             */
/*   Updated: 2024/11/23 21:15:24 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_REGISTER_TRIGGER_H
# define BG_REGISTER_TRIGGER_H

typedef struct ent_s
{
	char	id;
	t_vec2	pos;
	t_vec4	enabled;
}	t_ent;

typedef struct trigger_s
{
	t_ent	*ents;
	size_t	size;
}	t_trigger;

t_trigger	*get_trigger(int act);
int			is_trigger_active(t_player *user, t_ent *ent);
#endif