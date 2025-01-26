/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:10:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:32:56 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/bgame/bg_register.h"

t_dvars	register_double(const char *name, double value, t_vec2f limit)
{
	t_dvars	tmp;

	xmemset(&tmp, 0, sizeof(tmp));
	tmp.type = VAR_TYPE_DOUBLE;
	tmp.dvalue = value;
	tmp.dvalue_default = value;
	tmp.dlimit = limit;
	tmp.hashname = fnv1a_hash(name);
	return (tmp);
}

t_dvars	register_int(const char *name, int value, t_vec2 limit)
{
	t_dvars	tmp;

	xmemset(&tmp, 0, sizeof(tmp));
	tmp.type = VAR_TYPE_INT;
	tmp.ivalue = value;
	tmp.ivalue_default = value;
	tmp.ilimit = limit;
	tmp.hashname = fnv1a_hash(name);
	return (tmp);
}

t_dvars	register_boolean(const char *name, int status)
{
	t_dvars	tmp;

	xmemset(&tmp, 0, sizeof(tmp));
	tmp.type = VAR_TYPE_BOOLEAN;
	tmp.ivalue = status;
	tmp.hashname = fnv1a_hash(name);
	return (tmp);
}

t_dvars	register_color(const char *name, __uint32_t color)
{
	t_dvars	tmp;

	xmemset(&tmp, 0, sizeof(tmp));
	tmp.type = VAR_TYPE_COLOR;
	tmp.cvalue = color;
	tmp.hashname = fnv1a_hash(name);
	return (tmp);
}
