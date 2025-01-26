/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_sound.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:07:31 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:38:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/game/g_sound.h"

void	playsound(char *file, int wait, int stop, int attenued)
{
	char	*base;
	char	tmp[256];

	if (attenued)
		base = "paplay --volume=1 sound/";
	else
		base = "paplay --volume=40000 sound/";
	xmemset(tmp, 0, 256);
	xmemcpy(tmp, base, xstrlen(base));
	if (stop)
		system("pkill -f paplay");
	if (fnv1a_hash(file) == 2166136261u)
		return ;
	xmemcpy(&tmp[xstrlen(base)], file, xstrlen(file));
	if (!wait)
		base = ".ogg &";
	else
		base = ".ogg";
	xmemcpy(&tmp[xstrlen(tmp)], base, xstrlen(base));
	system(tmp);
}
