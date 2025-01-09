/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:42:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/08 03:18:20 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	sl_sqrt(int nb)
{
	int	i;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	i = 0;
	while (i <= nb / 2 && i <= 46341)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}

int	randintrange(int min, int max)
{
	return (min + rand() % (max - min + 1));
}

void	set_value(void *adr, __uint32_t val)
{
	*(__uint32_t *)adr = val;
}

__uint32_t	get_value(void *adr)
{
	return (*(__uint32_t *)adr);
}

clock_t	get_fps(clock_t cpu)
{
	float	s;

	cpu = clock() - cpu;
	s = (double)cpu / 1000000;
	cpu = 1 / s;
	return (cpu);
}
