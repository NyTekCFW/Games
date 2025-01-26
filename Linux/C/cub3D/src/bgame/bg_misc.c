/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:32:08 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:41:02 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"
#include "../../includes/bgame/bg_register.h"

static void	com_registerdvars(t_vars *var)
{
	var->com_maxfps = \
		register_int("com_maxfps", 30, (t_vec2){15, 144});
	var->com_timescale = \
		register_double("com_timescale", 1.0f, (t_vec2f){0.5f, 2.0f});
}

static void	bg_registerdvars(t_vars *var)
{
	var->bg_brightness = \
		register_double("bg_brightness", 0.5f, \
		(t_vec2f){0.0f, 1.5f});
	var->bg_flashlight_radius = \
		register_double("bg_flashlight_radius", 40.0f, \
		(t_vec2f){60.0f, 100.0f});
	var->bg_flashlight_color = \
		register_color("bg_flashlight_color", 0xFFFFFF);
	var->bg_shadow_radius = \
		register_double("bg_shadow_radius", 1.0f, (t_vec2f){0.05f, 2.0f});
}

static void	cg_registerdvars(t_vars *v)
{
	v->cg_gun_x = register_double("cg_gun_x", 1.0f, (t_vec2f){0.90f, 1.10f});
	v->cg_gun_y = register_double("cg_gun_y", 1.3f, (t_vec2f){0.88f, 1.60f});
	v->cg_aspect = \
		register_double("cg_aspect", -1.60f, (t_vec2f){-1.85f, 1.85f});
	v->cg_minimap_zoom = register_int("cg_minimap_zoom", 2, (t_vec2){1, 10});
	v->cg_flashlight_enable = register_boolean("cg_flashlight_enable", 1);
	v->cg_shadow_enable = register_boolean("cg_shadow_enable", 1);
	v->cg_rgb_ceil = register_boolean("cg_rgb_ceil", 0);
	v->cg_rgb_floor = register_boolean("cg_rgb_floor", 0);
	v->cg_mouse_fix = register_boolean("cg_mouse_fix", 0);
}

void	g_registerdvars(void)
{
	t_vars	*var;

	var = get_var();
	if (var)
	{
		var->g_speed = register_double("g_speed", 0.02f, \
				(t_vec2f){0.005f, 0.04f});
		com_registerdvars(var);
		bg_registerdvars(var);
		cg_registerdvars(var);
	}
}
