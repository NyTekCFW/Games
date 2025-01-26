/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_misc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:42:19 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/07 08:23:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_MISC_H
# define BG_MISC_H

enum e_type_var
{
	VAR_TYPE_DOUBLE = 0,
	VAR_TYPE_INT,
	VAR_TYPE_BOOLEAN,
	VAR_TYPE_COLOR,
};

typedef struct dvar_s
{
	__uint32_t	hashname;
	int			type;
	double		dvalue;
	double		dvalue_default;
	t_vec2f		dlimit;
	int			ivalue;
	int			ivalue_default;
	t_vec2		ilimit;
	__uint32_t	cvalue;
}	t_dvars;

/*
g_ = global variable
bg = bgame variable
cg_ = client variable
com = external variable
*/
typedef struct var_s
{
	t_dvars	g_speed;
	t_dvars	bg_shadow_radius;
	t_dvars	bg_flashlight_radius;
	t_dvars	bg_brightness;
	t_dvars	bg_flashlight_color;
	t_dvars	cg_gun_x;
	t_dvars	cg_gun_y;
	t_dvars	cg_minimap_zoom;
	t_dvars	cg_mouse_fix;
	t_dvars	cg_aspect;
	t_dvars	cg_flashlight_enable;
	t_dvars	cg_shadow_enable;
	t_dvars	com_timescale;
	t_dvars	com_maxfps;
	t_dvars	cg_rgb_floor;
	t_dvars	cg_rgb_ceil;
}	t_vars;

t_dvars	*dvar_findvar(const char*name);
void	*getvar(const char *name);
void	g_registerdvars(void);
#endif
