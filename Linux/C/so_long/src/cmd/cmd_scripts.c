/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_scripts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:48:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/26 07:29:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	add_cmd(t_core *core, void (*(func))(), char *name)
{
	t_cmdx	*current;
	t_cmdx	*newl;

	newl = (t_cmdx *)malloc(sizeof(t_cmdx));
	sl_memset(newl, 0, sizeof(t_cmdx));
	if (!newl)
		return ;
	current = get_cmd_list(core);
	while (current->next)
		current = current->next;
	if (!current)
		return ;
	newl->func = func;
	newl->name = sl_hashstr(name);
	newl->next = NULL;
	current->next = newl;
}

static t_cmdx	*cmd_f(t_core *core, char *argv)
{
	t_cmdx	*sc_l;

	sc_l = get_cmd_list(core);
	while (sc_l && sc_l->name != sl_hashstr(argv))
		sc_l = sc_l->next;
	if (!sc_l)
		return ((void *)0);
	return (sc_l);
}

void	init_cmd(t_core *core)
{
	t_cmdx	*sc_l;

	sc_l = get_cmd_list(core);
	sc_l->func = cmd_x2xp_f;
	sc_l->name = sl_hashstr("doublexp");
	sc_l->next = NULL;
	add_cmd(core, cmd_god_f, "god");
	add_cmd(core, cmd_speed_f, "sprint");
	add_cmd(core, cmd_info_f, "showinfo");
	add_cmd(core, cmd_quit_f, "quit");
}

void	clear_all_cmd(t_core *core)
{
	t_cmdx	*prev;
	t_cmdx	*list;

	list = get_cmd_list(core);
	while (list)
	{
		while (list->next)
		{
			prev = list;
			list = list->next;
		}
		sl_memset(list, 0, sizeof(t_cmdx));
		if (prev->next)
		{
			free(prev->next);
			prev->next = NULL;
			list = get_cmd_list(core);
		}
		else
			break ;
	}
}

void	execute_cmd(t_core *core)
{
	t_cmdx	*sc;

	sc = cmd_f(core, get_cmd(core)->buffer);
	if (sc && sc->func)
		sc->func(core);
	else
		print("Command not found");
}
