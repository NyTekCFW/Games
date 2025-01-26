/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:53:51 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:36:34 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

int	ent_is_solid(char c)
{
	if (c == '1' || c == 'K' || c == '[' || c == '+' || \
		c == ']' || c == '}' || c == '{' || c == 'D' || \
		c == 'P')
		return (1);
	return (0);
}

int	ent_is_ground(char c)
{
	if (c == '0' || c == 'T')
		return (1);
	return (0);
}

int	ent_is_trap(char c)
{
	if (c == 'D')
		return (1);
	return (0);
}

int	ent_is_trigger(char c)
{
	if (c == 'K' || c == 'T' || c == '[' || \
		c == ']' || c == '}' || c == '{' || c == '+' || \
		c == 'P')
		return (1);
	return (0);
}

int	ent_is_valid(char c)
{
	if (c == '1' || c == '0' || c == 'K' || c == 'T' || c == '{' || c == '}'
		|| c == '[' || c == ']' || c == '+' || c == ' ' || c == 'D' || c == 'P'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
