/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapons.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:53:14 by lchiva            #+#    #+#             */
/*   Updated: 2024/10/22 17:01:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SP_WEAPONS_H
# define SP_WEAPONS_H

void	give_weapon(char *name, __uint32_t clip, __uint32_t stock);
void	give_max_ammo(void);
int		can_get_ammo(void);
void	take_weapon(void);
void	weapon_fired(void);
void	weapon_reload(void);
void	get_weapon_info(void);
void	run_weapon_anim(const char *anim, int id);
#endif