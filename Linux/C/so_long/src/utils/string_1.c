/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 06:13:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/04 15:04:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	sl_isspace(int c)
{
	if ((c >= 0x09 && c <= 0x0D) || (c == 0x20))
		return (1);
	return (0);
}

void	sl_putnbr(__uint32_t n)
{
	char	c;

	if (n >= 10)
	{
		sl_putnbr(n / 10);
		sl_putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

int	sl_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	mp;

	mp = 1;
	res = 0;
	i = 0;
	while (nptr[i] && sl_isspace(nptr[i]))
		i++;
	if ((nptr[i] && nptr[i] == '+') || (nptr[i] && nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			mp *= -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= 0x30 && nptr[i] <= 0x39)
		res = (res * 10) + (nptr[i++] - 0x30);
	return (res * mp);
}

void	insert_str(char *buffer, char *str, size_t buffer_size)
{
	size_t	i;

	i = 0;
	while (str[i] && i < buffer_size)
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = 0;
}

void	print(char *str)
{
	size_t	len;

	len = sl_strlen(str);
	write(1, str, len);
	if (str[len - 1] != '\n')
		write(1, "\n", 1);
}
