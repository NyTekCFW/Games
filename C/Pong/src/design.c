/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 01:48:35 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/26 21:02:18 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	new_ball_velocity(t_ml *lx, int xfix, int yfix)
{
	if (xfix)
		lx->game.b_velocity.x = xorrandint(-3, 3);
	if (yfix)
		lx->game.b_velocity.y = xorrandint(-3, 3);
	while (xfix && lx->game.b_velocity.x >= -1 && lx->game.b_velocity.x <= 1)
		lx->game.b_velocity.x = xorrandint(-3, 3);
	while (yfix && lx->game.b_velocity.y >= -1 && lx->game.b_velocity.y <= 1)
		lx->game.b_velocity.y = xorrandint(-3, 3);
}

void	init_data(void)
{
	t_ml		*lx = gmlx(ACT_GET);
	t_shaders	*sh = get_img("framework");
	t_menu		*menu = dbg_menu(ACT_INIT);
	int			height;

	if (lx && sh)
	{
		height = (((sh->img.height / 2) + (sh->img.height / 4)) / 4) / 2;
		lx->game.p_origin[PLAYER_0] = (t_vec2){20, (sh->img.height / 2) - height};
		lx->game.p_origin[PLAYER_1] = (t_vec2){sh->img.width - 23, (sh->img.height / 2) - height};
		lx->game.b_origin = (t_vec2){(sh->img.width / 2) - 2, (sh->img.height / 2) - 2};
		lx->game.p_score[PLAYER_0] = 0;
		lx->game.p_score[PLAYER_1] = 0;
		lx->game.p_bbox_rng[PLAYER_0] = (t_vec4){-8, (sh->img.height / 2) - (sh->img.height / 4), 11, (height  * 16) / 3};
		lx->game.p_bbox_rng[PLAYER_1] = (t_vec4){sh->img.width - 3, (sh->img.height / 2) - (sh->img.height / 4), lx->width + 20, (height  * 16) / 3};//+ ((float)height / 3)};
		lx->game.p_box_rng[PLAYER_0] = (t_vec4){lx->game.p_origin[PLAYER_0].x - 4, lx->game.p_origin[PLAYER_0].y, lx->game.p_origin[PLAYER_0].x + 8, lx->game.p_origin[PLAYER_0].y + (height * 2)};
		lx->game.p_box_rng[PLAYER_1] = (t_vec4){lx->game.p_origin[PLAYER_1].x - 4, lx->game.p_origin[PLAYER_1].y, lx->game.p_origin[PLAYER_1].x + 4, lx->game.p_origin[PLAYER_1].y + (height * 2)};
		lx->game.remaiming_time = 100000;
		lx->game.fps = 120;
		lx->game.timescale = 1.0;
		new_ball_velocity(lx, 1, 1);
		dbg_add_slider("ImGUI x : ", OPT_INT, &menu->_pos.x, (t_vec2f){0, lx->width});
		dbg_add_slider("ImGUI y : ", OPT_INT, &menu->_pos.y, (t_vec2f){0, lx->height});
		dbg_add_slider("Player 0 score : ", OPT_INT, &lx->game.p_score[PLAYER_0], (t_vec2f){0, 0x7FFFFFFF});
		dbg_add_slider("Player 1 score : ", OPT_INT, &lx->game.p_score[PLAYER_1], (t_vec2f){0, 0x7FFFFFFF});
		dbg_add_slider("Velocity x : ", OPT_INT, &lx->game.b_velocity.x, (t_vec2f){-4, 4});
		dbg_add_slider("Velocity y : ", OPT_INT, &lx->game.b_velocity.y, (t_vec2f){-4, 4});
		dbg_add_slider("Ball position x : ", OPT_INT, &lx->game.b_origin.x, (t_vec2f){0, lx->width});
		dbg_add_slider("Ball position y : ", OPT_INT, &lx->game.b_origin.y, (t_vec2f){0, lx->height});
		dbg_add_slider("Player 0 position x : ", OPT_INT, &lx->game.p_origin[PLAYER_0].x, (t_vec2f){0, lx->width});
		dbg_add_slider("Player 0 position y : ", OPT_INT, &lx->game.p_origin[PLAYER_0].y, (t_vec2f){0, lx->height});
		dbg_add_slider("Player 1 position x : ", OPT_INT, &lx->game.p_origin[PLAYER_1].x, (t_vec2f){0, lx->width});
		dbg_add_slider("Player 1 position y : ", OPT_INT, &lx->game.p_origin[PLAYER_1].y, (t_vec2f){0, lx->height});
		dbg_add_slider("Timescale: ", OPT_FLOAT, &lx->game.timescale, (t_vec2f){0.3f, 2.0f});
		dbg_add_slider("FPS : ", OPT_INT, &lx->game.fps, (t_vec2f){20, 200});
		dbg_add_bool("Show Hit Box :", &lx->game.hit_box);
		dbg_add_bool("Show Wireframe :", &lx->game.wireframe);
	}
}

void draw_bkg(void)
{
	t_vec2		u = {-1, -1};
	t_shaders	*sh = get_img("framework");
	__uint32_t	addr;

	if (sh)
	{
		while (++u.y < sh->img.height)
		{
			u.x = -1;
			while (++u.x < sh->img.width)
			{
				addr = get_px_adr(&sh->img, u);
				if (u.y < 3)
					set_color(&sh->img, addr, 0xff0000);
				else if (u.y > sh->img.height - 3)
					set_color(&sh->img, addr, 0xff0000);
				else if (u.y < (sh->img.height / 2) - (sh->img.height / 4) || u.y > (sh->img.height / 2) + (sh->img.height / 4))
				{
					if (u.x < 3 || u.x > sh->img.width - 3)
						set_color(&sh->img, addr, 0xff0000);
				}
			}
		}
	}
}

void	draw_players(void)
{
	t_prim		s;
	t_ml		*lx = gmlx(ACT_GET);
	t_shaders	*sh = get_img("framework");
	int			height;

	if (lx && sh)
	{
		height = ((sh->img.height / 2) + (sh->img.height / 4)) / 4;
		lx->game.p_box_rng[PLAYER_0] = (t_vec4){lx->game.p_origin[PLAYER_0].x - 2, lx->game.p_origin[PLAYER_0].y - 2, 10, height + 4};
		lx->game.p_box_rng[PLAYER_1] = (t_vec4){lx->game.p_origin[PLAYER_1].x - 4, lx->game.p_origin[PLAYER_1].y - 2, 10, height + 4};
		s = ml_quad(lx->game.p_origin[PLAYER_0], (t_vec2){3, height}, 0xfffF);
		ml_savemesh(&s, "framework");
		ml_setmode(&s, lx->game.wireframe);
		ml_end(&s);
		s = ml_quad(lx->game.p_origin[PLAYER_1], (t_vec2){3, height}, 0xfffF);
		ml_savemesh(&s, "framework");
		ml_setmode(&s, lx->game.wireframe);
		ml_end(&s);
	}
}

void	draw_scores(void)
{
	t_ml		*lx = gmlx(ACT_GET);
	t_shaders	*sh = get_img("framework");
	char		buffer[64];
	char		*tmp;
	size_t		len;

	if (lx && sh)
	{
		xmemset(buffer, 0, sizeof(buffer));
		tmp = va_hex((long)lx->game.p_score[PLAYER_0], 10);
		len = xstrlen(tmp);
		xstrcpy(buffer, tmp);
		xfree((void **)&tmp);
		xstrcpy(buffer + len, " - ");
		len += 3;
		tmp = va_hex((long)lx->game.p_score[PLAYER_1], 10);
		xstrcpy(buffer + len, tmp);
		xfree((void **)&tmp);
		typewritter("framework", buffer, (t_vec2){(sh->img.width / 2) - (r_textwidth(buffer) / 2), 10});
	}
}


void	draw_ball(void)
{
	t_prim	s;
	t_shaders	*sh = get_img("framework");
	t_ml		*lx = gmlx(ACT_GET);
	int			i;

	if (lx && sh)
	{
		if (lx->game.b_origin.y < 4)
		{
			lx->game.b_origin.y = 4;
			new_ball_velocity(lx, 0, 1);
		}
		else if (lx->game.b_origin.y > sh->img.height - 8)
		{
			lx->game.b_origin.y = sh->img.height - 8;
			new_ball_velocity(lx, 0, 1);
		}
		else if (lx->game.b_origin.y < (sh->img.height / 2) - (sh->img.height / 4)
				|| lx->game.b_origin.y > (sh->img.height / 2) + (sh->img.height / 4))
		{
			if (lx->game.b_origin.x < 4)
			{
				lx->game.b_origin.x = 4;
				new_ball_velocity(lx, 1, 0);
				
			}
			else if (lx->game.b_origin.x > sh->img.width - 8)
			{
				lx->game.b_origin.x = sh->img.width - 8;
				new_ball_velocity(lx, 1, 0);
			}
		}
		i = -1;
		while (++i < PLAYER_MAX)
		{
			if (lx->game.hit_box)
			{
				s = ml_quad((t_vec2){lx->game.p_box_rng[PLAYER_0].x, lx->game.p_box_rng[PLAYER_0].y}, (t_vec2){lx->game.p_box_rng[PLAYER_0].z, lx->game.p_box_rng[PLAYER_0].w}, 0xff0000);
				ml_savemesh(&s, "framework");
				ml_setmode(&s, lx->game.wireframe);
				ml_end(&s);
				s = ml_quad((t_vec2){lx->game.p_box_rng[PLAYER_1].x, lx->game.p_box_rng[PLAYER_1].y}, (t_vec2){lx->game.p_box_rng[PLAYER_1].z, lx->game.p_box_rng[PLAYER_1].w}, 0xff0000);
				ml_savemesh(&s, "framework");
				ml_setmode(&s, lx->game.wireframe);
				ml_end(&s);
				s = ml_quad((t_vec2){lx->game.p_bbox_rng[PLAYER_0].x, lx->game.p_bbox_rng[PLAYER_0].y}, (t_vec2){lx->game.p_bbox_rng[PLAYER_0].z, lx->game.p_bbox_rng[PLAYER_0].w}, 0xff00ff);
				ml_savemesh(&s, "framework");
				ml_setmode(&s, lx->game.wireframe);
				ml_end(&s);
				s = ml_quad((t_vec2){lx->game.p_bbox_rng[PLAYER_1].x, lx->game.p_bbox_rng[PLAYER_1].y}, (t_vec2){lx->game.p_bbox_rng[PLAYER_1].z, lx->game.p_bbox_rng[PLAYER_1].w}, 0xff00ff);
				ml_savemesh(&s, "framework");
				ml_setmode(&s, lx->game.wireframe);
				ml_end(&s);
			}
			if (is_in_range((t_vec2){lx->game.p_bbox_rng[i].x, lx->game.p_bbox_rng[i].y}, lx->game.b_origin,
				(t_vec2){lx->game.p_bbox_rng[i].z, lx->game.p_bbox_rng[i].w}))
			{
				if (i == 0)
					lx->game.p_score[PLAYER_1]++;
				else
					lx->game.p_score[PLAYER_0]++;
				lx->game.b_origin = (t_vec2){(sh->img.width / 2) - 2, (sh->img.height / 2) - 2};
				new_ball_velocity(lx, 1, 1);
				break ;
			}
			else if (is_in_range((t_vec2){lx->game.p_box_rng[i].x, lx->game.p_box_rng[i].y}, lx->game.b_origin,
				(t_vec2){lx->game.p_box_rng[i].z, lx->game.p_box_rng[i].w}))
			{
				lx->game.b_velocity.x *= -1;
				lx->game.b_velocity.y *= -1;
				break ;
			}
		}
		s = ml_quad(lx->game.b_origin, (t_vec2){4, 4}, 0xFFFFff);
		ml_setmode(&s, lx->game.wireframe);
		ml_savemesh(&s, "framework");
		ml_end(&s);
	}
}

void	draw_game(void)
{
	draw_bkg();
	draw_ball();
	draw_players();
	draw_scores();
}
