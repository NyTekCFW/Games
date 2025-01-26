/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   parsing_05.c                                                             */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 26/01/2025 17:38:37 by NyTekCFW                                 */
/*   Updated: 26/01/2025 17:38:42 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/core/parsing.h"

void	test_right(t_vec2 u, t_vec2 d, char **map, int *a)
{
	int	x;

	x = u.x;
	while (x + 1 < d.x)
	{
		if (map[u.y][x + 1] == '\n' || !map[u.y][x + 1])
			break ;
		if (map[u.y][x + 1] == '1')
		{
			++(*a);
			break ;
		}
		++x;
	}
}

void	test_left(t_vec2 u, char **map, int *a)
{
	int	x;

	x = u.x;
	while (x - 1 > -1)
	{
		if (map[u.y][x - 1] == '\n' || !map[u.y][x - 1])
			break ;
		if (map[u.y][x - 1] == '1')
		{
			++(*a);
			break ;
		}
		--x;
	}
}

void	test_down(t_vec2 u, t_vec2 d, char **map, int *a)
{
	int	y;

	y = u.y;
	while (y + 1 < d.y)
	{
		if (map[y + 1][u.x] == '\n' || !map[y + 1][u.x])
			break ;
		if (map[y + 1][u.x] == '1')
		{
			++(*a);
			break ;
		}
		++y;
	}
}

void	test_up(t_vec2 u, char **map, int *a)
{
	int	y;

	y = u.y;
	while (y - 1 > -1)
	{
		if (map[y - 1][u.x] == '\n' || !map[y - 1][u.x])
			break ;
		if (map[y - 1][u.x] == '1')
		{
			++(*a);
			break ;
		}
		--y;
	}
}

int	floor_test(char **map, t_vec2 d)
{
	int		a;
	t_vec2	u;

	u = (t_vec2){0, 0};
	while (u.y < d.y)
	{
		u.x = 0;
		while (u.x < d.x)
		{
			if (map[u.y][u.x] == '0')
			{
				a = 0;
				test_right(u, d, map, &a);
				test_left(u, map, &a);
				test_down(u, d, map, &a);
				test_up(u, map, &a);
				if ((a != 4))
					return (tmp_map_clear(map, d),
						printf("Error\nmap not filled\n"), 0);
			}
			++u.x;
		}
		++u.y;
	}
	return (tmp_map_clear(map, d), 1);
}
