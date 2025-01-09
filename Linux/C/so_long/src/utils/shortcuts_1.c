/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:38:45 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/14 10:05:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_color	*get_color(t_core *core)
{
	return (&core->color);
}

t_hook	*get_hook(t_core *core)
{
	return (&core->hook);
}

t_account	*get_account(t_core *core)
{
	return (&core->account);
}

t_submenu	*get_submenu(t_core *core)
{
	return (&core->submenu[get_status(core)]);
}

char	**get_map(t_core *core)
{
	return (get_game(core)->map);
}
