/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_cfg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:49:22 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/02 17:28:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	get_reso(t_core *core, int load)
{
	if (!load)
		get_win_arg(core, hstr_reso, r_max);
	if (get_mlx(core)->result_attempt == r_error)
		return (0);
	if (get_mlx(core)->result_attempt == r_480p)
		apply_reso(core, 720, 480, r_480p);
	else if (get_mlx(core)->result_attempt == r_720p)
		apply_reso(core, 1280, 720, r_720p);
	else if (get_mlx(core)->result_attempt == r_1080p)
		apply_reso(core, 1920, 1080, r_1080p);
	else if (get_mlx(core)->result_attempt == r_1440p)
		apply_reso(core, 2560, 1440, r_1440p);
	else if (get_mlx(core)->result_attempt == r_2160p)
		apply_reso(core, 3840, 2160, r_2160p);
	else
		return (0);
	return (1);
}

static int	get_keyboard(t_core *core)
{
	int	uid;

	get_win_arg(core, hstr_keyboard, k_max);
	if (get_mlx(core)->result_attempt == k_error)
		return (0);
	if (get_mlx(core)->result_attempt == k_qwerty)
		uid = k_qwerty;
	else if (get_mlx(core)->result_attempt == k_azerty)
		uid = k_azerty;
	get_account(core)->keyboard = uid;
	return (1);
}

static int	init_config(t_core *core)
{
	get_mlx(core)->result_attempt = get_account(core)->reso;
	colors_init(core);
	init_cmd(core);
	init_anim(core);
	get_reso(core, 1);
	apply_keybinds(core);
	init_submenu(core);
	init_img(core);
	return (1);
}

int	win_config(t_core *core)
{
	int	save_status;

	save_status = read_save(core);
	get_mlx(core)->ptr = mlx_init();
	if (!get_mlx(core)->ptr)
		return (win_error(core));
	mlx_get_screen_size(
		get_mlx(core)->ptr, &get_mlx(core)->width, &get_mlx(core)->height);
	if (!save_status)
	{
		if (!get_reso(core, 0) || !get_keyboard(core) || !make_save(core))
			return (win_error(core));
	}
	return (init_config(core));
}
