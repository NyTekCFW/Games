/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:56:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/21 06:06:22 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	init_item_count(t_core *core, char *ent, t_vec2 px)
{
	if (*ent == g_collect)
		get_game(core)->ents[c_collect]++;
	else if (*ent == g_exit)
		get_game(core)->ents[c_exit]++;
	else if (*ent == g_player)
	{
		get_game(core)->ents[c_player]++;
		get_client(core)->pos = px;
	}
	else if (*ent == g_axis)
		get_game(core)->ents[c_axis]++;
}

static int	is_filled_y(t_core *core, t_vec2 px)
{
	char	**map;
	t_vec3	yr;

	yr = vec3t(0, 0, get_game(core)->map_max.y);
	map = get_map(core);
	while ((px.y + yr.x) > -1 && map[px.y + yr.x] && map[px.y + yr.x][px.x])
	{
		if (map[px.y + yr.x][px.x] == '1')
		{
			yr.y++;
			break ;
		}
		yr.x--;
	}
	while ((px.y + yr.x) < yr.z && map[px.y + yr.x] && map[px.y + yr.x][px.x])
	{
		if (map[px.y + yr.x][px.x] == '1')
		{
			yr.y++;
			break ;
		}
		yr.x++;
	}
	return ((yr.y == 2));
}

static int	is_filled_x(t_core *core, t_vec2 px)
{
	char	**map;
	t_vec3	yr;

	yr = vec3t(0, 0, get_game(core)->map_max.x);
	map = get_map(core);
	while ((px.x + yr.x) > -1 && map[px.y] && map[px.y][px.x + yr.x])
	{
		if (map[px.y][px.x + yr.x] == '1')
		{
			yr.y++;
			break ;
		}
		yr.x--;
	}
	while ((px.x + yr.x) < yr.z && map[px.y] && map[px.y][px.x + yr.x])
	{
		if (map[px.y][px.x + yr.x] == '1')
		{
			yr.y++;
			break ;
		}
		yr.x++;
	}
	return ((yr.y == 2));
}

static void	check_is_filled(t_core *core, char *ent, t_vec2 px)
{
	if (*ent == '0')
	{
		if (!is_filled_y(core, px) || !is_filled_x(core, px))
		{
			print("Map is not filled!");
			win_error(core);
		}
	}
}

int	map_is_valid(t_core *core)
{
	t_game	*gm;

	gm = get_game(core);
	browse_map(core, init_item_count);
	browse_map(core, check_is_filled);
	if (gm->ents[c_collect] < 1)
		return (print("Error rupee!"), 0);
	if (gm->ents[c_exit] != 1)
		return (print("Error exit!"), 0);
	if (gm->ents[c_player] != 1)
		return (print("Error player!"), 0);
	check_path(core);
	return (1);
}
