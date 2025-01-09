/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_binds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:15:28 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/20 07:46:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	binds_main(int ks, t_core *core)
{
	if (ks == XK_Escape)
		return (win_exit(core));
	return (0);
}

static void	pmove(t_core *core, int *abs, t_vec2 vks, int *pressed)
{
	*pressed = 1;
	p_move(core, abs, vks.x, vks.y);
}

int	binds_resume(int ks, t_core *core)
{
	int		spm;

	if (get_client(core)->is_meleeing)
		return (0);
	spm = 4 + (flag_status(core, p_speed) * 2);
	if ((ks == get_client(core)->keybind[kb_up])
		|| (ks == XK_Up) || (core->ks.up))
		pmove(core, &get_client(core)->origin.y,
			vec2t(spm * -1, kb_up), &core->ks.up);
	else if ((ks == get_client(core)->keybind[kb_down])
		|| (ks == XK_Down) || (core->ks.dw))
		pmove(core, &get_client(core)->origin.y,
			vec2t(spm, kb_down), &core->ks.dw);
	if ((ks == get_client(core)->keybind[kb_left])
		|| (ks == XK_Left) || (core->ks.lf))
		pmove(core, &get_client(core)->origin.x,
			vec2t(spm * -1, kb_left), &core->ks.lf);
	else if ((ks == get_client(core)->keybind[kb_right])
		|| (ks == XK_Right) || (core->ks.rt))
		pmove(core, &get_client(core)->origin.x,
			vec2t(spm, kb_right), &core->ks.rt);
	if (ks == XK_Escape)
		return (win_exit(core));
	return (0);
}

int	binds_pause(int ks, t_core *core)
{
	if (ks == XK_u)
		draw_pause_cmds(core);
	else if (ks == XK_i)
		send_command(core);
	else if (ks == XK_Escape)
		return (win_exit(core));
	return (0);
}

int	binds_cmd(int ks, t_core *core)
{
	if (get_cmd(core)->is_open && get_status(core) == status_cmd)
	{
		if (get_cmd(core)->cursor > 0 && ks == XK_BackSpace)
			get_cmd(core)->buffer[--get_cmd(core)->cursor] = 0;
		else if (ks >= 0x20 && ks < 0x7F && get_cmd(core)->cursor < 31)
			get_cmd(core)->buffer[get_cmd(core)->cursor++] = ks;
		else if (ks == XK_Return || ks == XK_Escape)
		{
			get_cmd(core)->buffer[get_cmd(core)->cursor] = 0;
			if (ks == XK_Return)
				execute_cmd(core);
			sl_memset(get_cmd(core)->buffer, 0, 32);
			get_cmd(core)->cursor = 0;
			get_cmd(core)->is_open = 0;
			set_status(core, status_pause);
		}
		draw_pause(core, 1);
	}
	return (0);
}
