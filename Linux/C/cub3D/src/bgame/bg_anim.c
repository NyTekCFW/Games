/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:38:37 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/04 14:33:47 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	increment_anim(t_vec2 *v, t_anim *anim)
{
	if (clock() >= anim->next_frametime)
	{
		if (v->y == 0 && v->x < anim->max_frame)
		{
			++v->x;
			if (v->x >= anim->max_frame)
				v->y = 1;
		}
		else if (v->y == 1 && v->x >= 0)
		{
			v->x -= 1;
			if (v->x < 0)
				anim->loop_anim = (t_vec2){0, 0};
		}
		anim->next_frametime = clock() + anim->frame_time;
	}
}

void	running_env_anim(void)
{
	int		id;
	t_anim	*anim;

	id = WORLD_ANIM_MM_FIRE;
	while (id < 3)
	{
		anim = get_wanim(id);
		if (anim)
			increment_anim(&anim->loop_anim, anim);
		++id;
	}
}

t_shaders	*get_anim_img(int id, char *base_name)
{
	t_anim		*anim;
	t_shaders	*sh;
	char		*str;
	size_t		len;

	str = NULL;
	sh = NULL;
	if (base_name)
	{
		anim = get_wanim(id);
		len = xstrlen(base_name) + 1;
		if (anim && xalloc((void **)&str, sizeof(char) * len, 1))
		{
			xstrcpy(str, base_name);
			str[len - 2] = anim->loop_anim.x + '0';
			sh = get_img(str);
			xfree((void **)&str);
		}
	}
	return (sh);
}

static void	_reg_anim(t_anim *anim, int id, int time, int max)
{
	if (anim)
	{
		anim->id = id;
		anim->frame_time = time;
		anim->max_frame = max;
		anim->loop_anim = (t_vec2){0, 0};
		anim->next_frametime = clock() + anim->frame_time;
	}
}

void	bg_register_world_anim(void)
{
	t_anim	*anim;

	anim = get_wanim(WORLD_ANIM_MM_FIRE);
	_reg_anim(anim, WORLD_ANIM_MM_FIRE, 125000, 1);
	anim = get_wanim(WORLD_ANIM_FIRE);
	_reg_anim(anim, WORLD_ANIM_FIRE, 50000, 3);
	anim = get_wanim(WORLD_ANIM_ZM);
	_reg_anim(anim, WORLD_ANIM_ZM, 40000, 9);
}
