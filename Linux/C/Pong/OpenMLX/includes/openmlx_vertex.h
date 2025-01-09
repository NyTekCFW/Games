/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_vertex.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:23:13 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/25 23:09:58 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_VERTEX_H
# define OPENMLX_VERTEX_H

typedef struct prim_s
{
	int			primitive;
	int			cpoint;
	int			mode;
	int			uv;
	int			wrapping;
	int			texture;
	int			overwrite;
	float		intensity;
	t_img		*img;
	t_img		*savemesh;
	t_vec2		point[360];
	__uint32_t	size;
	__uint32_t	color_texture;
	__uint32_t	color;
}	t_prim;

//vertex settings
t_prim	ml_begin(int prim);
void	ml_vertex(t_prim *s, t_vec2 origin);
void	ml_color(t_prim *s, __uint32_t color);
void	ml_size(t_prim *s, __uint32_t size);
void	ml_setmode(t_prim *s, int mode);
void	ml_settexture(t_prim *s, char *name);
void	ml_setintensity(t_prim *s, float i);
void	ml_setuv(t_prim *s, int uv);
void	ml_setwrap(t_prim *s, int wrap);
void	ml_savemesh(t_prim *s, char *sh);
void	ml_overwrite(t_prim *s, int overwrite);
void	ml_overwrite_fix(t_prim *s, t_vec4 *ijt);
//display
void	ml_end(t_prim *s);
void	create_img_mesh(t_prim *s, char *name);
//draw method used by ml_end
void	ml_put_pixel(int x, int y, __uint32_t color);
void	ml_draw_points(t_prim *s);
void	ml_draw_lines(t_prim *s, int w, int e);
void	ml_draw_line_sl(t_prim *s);
void	ml_draw_triangles(t_prim *s);
void	ml_draw_quads(t_prim *s);
void	ml_draw_quad_strip(t_prim *s);
void	ml_draw_polygon(t_prim *s);
//vertex and color check
int		is_valid_color(__uint32_t c);
int		ml_can_draw(t_prim *s, t_vec2 xy);
//build form
t_prim	ml_quad(t_vec2 origin, t_vec2 scale, __uint32_t color);
t_prim	ml_triangle(t_vec2 p1, t_vec2 p2, t_vec2 p3, __uint32_t color);
#endif