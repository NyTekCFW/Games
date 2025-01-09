/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:07:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/06 20:23:27 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_cmd	*get_cmd(t_core *core)
{
	return (&get_game(core)->cmd);
}

t_cmdx	*get_cmd_list(t_core *core)
{
	return (&get_cmd(core)->list);
}

t_client	*get_client(t_core *core)
{
	return (&get_game(core)->client);
}

t_mlx	*get_mlx(t_core *core)
{
	return (&core->mlx);
}

t_game	*get_game(t_core *core)
{
	return (&core->game);
}
