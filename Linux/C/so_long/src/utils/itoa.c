/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 06:36:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/26 08:22:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static clock_t	alloc_lenght(clock_t n)
{
	clock_t	total_lenght;

	if (n < 0)
	{
		total_lenght = 2;
		n = n * (-1);
	}
	else
		total_lenght = 1;
	while ((n / 10) > 0)
	{
		n = n / 10;
		total_lenght++;
	}
	return (total_lenght);
}

static void	check(clock_t *nbr, char *buffer)
{
	if (*nbr < 0)
	{
		*nbr = *nbr * (-1);
		buffer[0] = '-';
	}
}

char	*sl_itoa(clock_t n)
{
	char	*buffer;
	clock_t	lenght;
	clock_t	i;
	clock_t	nbr;

	nbr = n;
	lenght = alloc_lenght(nbr);
	buffer = sl_calloc(sizeof(char), lenght + 1);
	if (!buffer)
		return (0);
	check(&nbr, buffer);
	i = lenght;
	if (nbr == 0)
		buffer[i - 1] = '0';
	while (nbr > 0)
	{
		buffer[i - 1] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
	buffer[lenght] = 0;
	return (buffer);
}
