/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_cfg_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:40:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/24 05:33:40 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	check_input(t_core *core, char *argv, int max)
{
	int	res;

	if (argv)
	{
		argv[sl_strlen(argv) - 1] = 0;
		if (sl_strlen(argv) < 2 && argv[0] >= 0x30
			&& argv[0] <= 0x39)
		{
			res = sl_atoi(argv);
			if (res >= 0 && res < max)
			{
				get_mlx(core)->attempt_init = 0;
				get_mlx(core)->result_attempt = res;
				return ;
			}
		}
	}
	print("Wrong input!\n");
	get_mlx(core)->attempt_init--;
	get_mlx(core)->result_attempt = -1;
}

static void	win_print_uid(unsigned long uid)
{
	char	*hd;
	char	*wr;

	hd = "Empty header uid\n";
	wr = "Empty text uid\n";
	if (uid == hstr_reso)
	{
		hd = "Pickup a Resolution :\n";
		wr = "0-480p\n1-720p\n2-1080p\n3-1440p\n4-2160p\n";
	}
	if (uid == hstr_keyboard)
	{
		hd = "What is your keyboard ? :\n";
		wr = "0-QWERTY\n1-AZERTY\n";
	}
	print(hd);
	print(wr);
	write(1, "Choice : ", 9);
}

void	get_win_arg(t_core *core, unsigned long uid, int max)
{
	char	*line;

	line = NULL;
	get_mlx(core)->attempt_init = 3;
	get_mlx(core)->result_attempt = -1;
	win_print_uid(uid);
	while (get_mlx(core)->attempt_init > 0)
	{
		line = gnl(0);
		check_input(core, line, max);
		free(line);
		line = NULL;
	}
}
