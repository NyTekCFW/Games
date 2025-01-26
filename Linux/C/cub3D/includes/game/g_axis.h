/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_axis.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:15:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 09:12:23 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_AXIS_H
# define G_AXIS_H

typedef struct axis_s
{
	clock_t		spawn_time;
	clock_t		attack_time;
	clock_t		intermission;
	clock_t		hitmarker_time;
	__uint32_t	dmg_color;
	int			health;
	int			maxhealth;
	int			is_headshot;
	int			damage;
	int			attack_damage;
	int			alive;
	int			init;
	int			round;
	int			total;
	int			is_intermission;
}	t_axis;

void	run_axis(void);
t_axis	*get_zm(void);
void	spawn_zm(t_axis *zm);
void	run_zm_logic(void);
void	display_game_over(void);
void	display_round(void);
#endif