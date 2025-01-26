/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:05:45 by lchiva            #+#    #+#             */
/*   Updated: 2025/01/15 20:08:30 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_file
{
	char		**map;
	char		*content;
	char		*pos;
	char		*texture_no;
	char		*texture_so;
	char		*texture_we;
	char		*texture_ea;
	int			begin;
	int			width;
	int			height;
	int			total_line;
	__uint32_t	color[2];
}	t_file;

char		*get_next_line(t_file *file);
char		*find_texture(t_file *file, char *v, int *flag);
char		*find_color(t_file *file, char *v, int *flag);
int			parse_map(t_file *file);
int			check_file(char *av);
int			check_arg(int argc, char **argv);
int			fill_file_map(void);
int			get_total_line(t_file *file);
int			line_color_check(const char *s);
int			is_first_word(const char *p, const char *v, int res);
t_file		*get_parsing_file(int act);
__uint32_t	check_valid_color(char *d, int *flag);
int			check_entry(int ac, char **av);
int			floor_test(char **map, t_vec2 d);
char		*search_tex2(char *v, char *tmp, char *tmp2, int *fd);
void		tmp_map_clear(char **map, t_vec2 d);
#endif