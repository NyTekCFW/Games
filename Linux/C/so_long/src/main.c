/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:02:15 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/28 03:24:28 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	is_a_ber(char *file)
{
	size_t	len;

	len = sl_strlen(file);
	if (len >= 5 && file[len - 4] == '.' && file[len - 3] == 'b'
		&& file[len - 2] == 'e' && file[len - 1] == 'r')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (argc != 2)
	{
		print("Error: number of arguments");
		return (1);
	}
	srand(time(NULL));
	sl_memset(&core, 0, sizeof(core));
	if (!is_a_ber(argv[1]))
		return (print("Not a .ber file!"), 0);
	if (init_map(&core, argv[1]))
	{
		check_files();
		win_maker(&core);
	}
	else
		win_error(&core);
	return (1);
}
