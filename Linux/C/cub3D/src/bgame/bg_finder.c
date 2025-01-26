/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_finder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:04:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:30:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

t_dvars	*dvar_findvar(const char *name)
{
	t_vars		*var;
	t_dvars		*dvar;
	__uint32_t	hash;
	size_t		i;

	i = 0;
	var = get_var();
	hash = fnv1a_hash(name);
	if (var)
	{
		while (i < (sizeof(t_vars) / sizeof(t_dvars)))
		{
			dvar = (t_dvars *)((__uint64_t)var + (sizeof(t_dvars) * i));
			if (dvar && dvar->hashname == hash)
				return (dvar);
			++i;
		}
	}
	return (NULL);
}

void	*getvar(const char *name)
{
	t_dvars		*var;
	t_player	*user;

	var = dvar_findvar(name);
	user = get_user();
	if (user)
	{
		if (var)
		{
			if (var->type == VAR_TYPE_DOUBLE)
				return (&var->dvalue);
			if (var->type == VAR_TYPE_INT || var->type == VAR_TYPE_BOOLEAN)
				return (&var->ivalue);
			if (VAR_TYPE_COLOR)
				return (&var->cvalue);
		}
	}
	return (&user->localclientnum);
}
