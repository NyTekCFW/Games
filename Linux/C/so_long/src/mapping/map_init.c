/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:30:19 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/28 03:23:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	isinarray(int arr[], int size, int c)
{
	int	i;

	i = 0;
	if (!arr || !*arr || !size)
		return (0);
	while (i < size)
	{
		if (arr[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	is_valid_ent(char c)
{
	int	ent[8];

	sl_memcpy(ent, (int []){g_axis, g_collect, g_exit, g_fire,
		g_ground, g_player, g_wall, '\n'}, sizeof(ent));
	return (isinarray(ent, 8, c));
}

static int	map_is_rectangle(t_core *core, char *map)
{
	t_vec4	wh;
	int		x;

	x = 0;
	wh = vec4t(0, 0, 0, sl_strlen(map));
	while (wh.z < wh.w && map[wh.z])
	{
		if (map[wh.z] && map[wh.z] != '\n')
			wh.x++;
		else if (map[wh.z] == '\n')
		{
			if (x > 0 && x != wh.x)
				return (0);
			x = wh.x;
			wh.y++;
			wh.x = 0;
		}
		if (!is_valid_ent(map[wh.z]))
			return (print("not a valid ent!"), 0);
		wh.z++;
	}
	get_game(core)->map_max = vec2t(x, wh.y + 1);
	if (wh.y + 1 == x)
		return (0);
	return (1);
}

void	stock(t_core *core, char *stack)
{
	int		i;
	t_vec2	max;

	max = get_game(core)->map_max;
	i = 0;
	core->game.map = (char **)malloc(max.y * sizeof(char *));
	if (core->game.map)
	{
		while (i < max.y)
		{
			core->game.map[i] = (char *)malloc((max.x * sizeof(char)) + 1);
			sl_memset(core->game.map[i], 0, max.x * sizeof(char));
			insert_str(core->game.map[i], stack, max.x);
			stack += max.x + 1;
			i++;
		}
	}
}

int	init_map(t_core *core, char *file)
{
	t_vec2	fd;
	char	*stack;

	fd = xopen(file);
	if (fd.x > 0 && fd.y > 0
		&& sl_alloc((void *)&stack, fd.y + 1, sizeof(char)))
	{
		if (read(fd.x, stack, fd.y) > 0)
		{
			if (map_is_rectangle(core, stack))
			{
				stock(core, stack);
				free(stack);
				close(fd.x);
				return (map_is_valid(core));
			}
			else
				print("map is not a rectangle!");
		}
	}
	close(fd.x);
	return (0);
}
