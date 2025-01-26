/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_axis_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:23:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:37:10 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_sound.h"
#include "../../includes/game/g_axis.h"
#include "../../includes/game/g_client_script.h"

void	display_game_over(void)
{
	char		tmp[40];
	char		*tmp2;
	t_axis		*zm;
	t_player	*user;

	zm = get_zm();
	user = get_user();
	if (zm && user && user->status == USER_DEAD)
	{
		xmemset(tmp, 0, 40 * sizeof(char));
		xstrcpy(tmp, "You Survived ");
		tmp2 = xitoa(zm->round);
		xstrcpy(&tmp[xstrlen(tmp)], tmp2);
		xstrcpy(&tmp[xstrlen(tmp)], " Rounds!");
		typewritter("framework", "Game Over", (t_vec2){559, 75});
		typewritter("framework", tmp, (t_vec2){455, 105});
		xfree((void **)&tmp2);
	}
}

void	display_round(void)
{
	t_axis	*zm;
	char	*tmp;

	zm = get_zm();
	if (zm)
	{
		tmp = xitoa(zm->round);
		if (tmp)
		{
			typewritter("framework", tmp, (t_vec2){15, 665});
			xfree((void **)&tmp);
		}
	}
}
