/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_client_script.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:32 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 09:11:30 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_CLIENT_SCRIPT_H
# define G_CLIENT_SCRIPT_H

void	scr_find_trigger_active(void);
void	scr_ammo_tracker(void);
int		scr_purchase(char new_id, char *current, int price, char *sound);
void	scr_trigger_perks(t_player *user, char c, int *dis);
void	dodamage(t_player *user, int c, int dmg);
void	add_score(__uint32_t add);
void	scr_trigger_pap(t_player *user, int *dis);
void	start_pause(void);
void	stop_pause(void);
#endif
