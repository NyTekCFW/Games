/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 02:27:36 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/16 19:37:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	playsound(char *file, int wait, int stop, int attenued)
{
	char	*base;
	char	tmp[256];

	if (attenued)
		base = "paplay --volume=30000 sound/";
	else
		base = "paplay --volume=40000 sound/";
	sl_memset(tmp, 0, 256);
	sl_memcpy(tmp, base, sl_strlen(base));
	if (stop)
		system("pkill -f paplay");
	if (sl_hashstr(file) == 2784)
		return ;
	sl_memcpy(&tmp[sl_strlen(base)], file, sl_strlen(file));
	if (!wait)
		base = ".ogg &";
	else
		base = ".ogg";
	sl_memcpy(&tmp[sl_strlen(tmp)], base, sl_strlen(base));
	system(tmp);
}
