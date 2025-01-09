/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:13:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/20 12:16:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include "sl_enum.h"
# include "sl_math.h"
# include "sl_ui.h"

# define PATH_SAVE "saves/config_user.bin"
# define BUFFER_SIZE 42

typedef struct cmdx_s
{
	void			(*(func))();
	__uint32_t		name;
	struct cmdx_s	*next;
}	t_cmdx;

typedef struct cmd_s
{
	int				is_open;
	int				cursor;
	char			buffer[32];
	t_cmdx			list;
}	t_cmd;

typedef struct imgx_s
{
	__uint32_t		file;
	int				width;
	int				height;
	t_img			img;
	struct imgx_s	*next;
}	t_imgx;

typedef struct mlx_s
{
	void		*ptr;
	void		*win;
	int			width;
	int			height;
	int			attempt_init;
	int			result_attempt;
}	t_mlx;

typedef struct account_s
{
	int			xp;
	int			level;
	__uint32_t	total_collected;
	__uint32_t	total_killed;
	__uint32_t	total_step;
	char		unused_mem[128];
	int			reso;
	int			keyboard;
}	t_account;

typedef struct hook_s
{
	int	(*binds)();
}	t_hook;

typedef struct client_s
{
	__uint32_t	step;
	__uint32_t	flags;
	int			health;
	int			dir;
	int			display;
	int			is_meleeing;
	int			new_zone;
	int			keybind[4];
	char		*lead_buff;
	char		*info_buff;
	t_vec2		origin;
	t_vec2		old_origin;
	t_vec2		zones;
	t_vec2		pos;
}	t_client;

typedef struct game_s
{
	char		**map;
	__uint16_t	ents[7];
	t_vec4		map_i;
	t_vec2		map_max;
	t_vec2		map_zone;
	t_vec2		map_rng;
	t_vec2		map_print;
	int			status;
	int			stop_proc;
	t_client	client;
	t_cmd		cmd;
}	t_game;

typedef struct anim_s
{
	clock_t		frame[9];
	clock_t		rate[5];
	char		max_status[5];
	char		status[5];
	char		name[5][32];
}	t_anim;

typedef struct control_s
{
	int	up;
	int	dw;
	int	lf;
	int	rt;
}	t_control;

typedef struct core_s
{
	t_account	account;
	t_color		color;
	t_mlx		mlx;
	t_hook		hook;
	t_game		game;
	t_submenu	submenu[5];
	t_imgx		shaders;
	t_anim		anim;
	t_control	ks;
}	t_core;

//color
void			colors_init(t_core *core);
void			fade_rgb(t_core *core);
__uint32_t		smooth_argb(long value, long new_value, long amount);
//shortcuts
t_cmd			*get_cmd(t_core *core);
t_cmdx			*get_cmd_list(t_core *core);
t_client		*get_client(t_core *core);
t_mlx			*get_mlx(t_core *core);
t_game			*get_game(t_core *core);
t_color			*get_color(t_core *core);
t_hook			*get_hook(t_core *core);
t_account		*get_account(t_core *core);
t_submenu		*get_submenu(t_core *core);
char			**get_map(t_core *core);
//memory
void			*sl_memcpy(void *dest, const void *src, size_t n);
void			*sl_memset(void *s, int c, size_t n);
void			*sl_calloc(size_t nmemb, size_t size);
int				sl_alloc(void **var, size_t nmemb, size_t ts);
//string
size_t			sl_strlen(const char *str);
__uint32_t		sl_hashstr(const char *str);
int				sl_strcmp(const char *s1, const char *s2);
int				sl_atoi(const char *nptr);
char			*sl_strchr(const char *s, int c);
char			*sl_strjoin(char *s1, char *s2);
char			*gnl(int fd);
char			*sl_itoa(clock_t n);
char			*sl_strrchr(const char *s, int c);
void			rp_join(char *buff, char *str);
void			sl_putnbr(__uint32_t n);
void			insert_str(char *buffer, char *str, size_t buffer_size);
void			print(char *str);
//binding keyboard
int				binds_resume(int ks, t_core *core);
int				binds_pause(int ks, t_core *core);
int				binds_main(int ks, t_core *core);
int				binds_cmd(int ks, t_core *core);
//hook
int				hook_key_release(int ks, t_core *core);
int				win_hook(t_core *core);
int				win_exit(t_core *core);
//savedata
int				read_save(t_core *core);
int				make_save(t_core *core);
//window
void			apply_keybinds(t_core *core);
void			apply_reso(t_core *core, int width, int height, int id);
void			get_win_arg(t_core *core, unsigned long uid, int max);
int				win_config(t_core *core);
void			win_maker(t_core *core);
int				win_error(t_core *core);
//cmd & flags
void			init_cmd(t_core *core);
void			clear_all_cmd(t_core *core);
void			execute_cmd(t_core *core);
void			send_command(t_core *core);
void			flag_set(t_core *core, __uint32_t flag);
void			flag_clear(t_core *core, __uint32_t flag);
int				flag_status(t_core *core, __uint32_t flag);
void			flag_print(char	*str, __uint32_t status);
void			cmd_god_f(t_core *core);
void			cmd_info_f(t_core *core);
void			cmd_x2xp_f(t_core *core);
void			cmd_speed_f(t_core *core);
void			cmd_quit_f(t_core *core);
//rendering
void			r_drawpix(t_core *core, t_vec2 *px, __uint32_t clr);
void			r_draw_box(t_img *img, t_ui ui);
void			r_drawtext(t_core *core, t_vec2 *xy, __uint32_t c, char *s);
int				r_textwidth(char *str);
void			r_centertext(t_core *core, t_ui ui, char *str);
void			r_line(t_core *core, t_ln *gnew);
void			r_draw_wall(t_core *core, t_ui ui);
//submenu
void			init_submenu(t_core *core);
void			render_submenu(t_core *core);
//button
int				button_click(int k, t_vec2 p, t_core *c, t_uibutton *b);
void			ui_play_button(t_core *core);
void			ui_resume_button(t_core *core);
//button func
void			leaderboard_free(t_core *core);
void			show_leaderboard(t_core *core);
//information
void			info_free(t_core *core);
void			show_info(t_core *core);
//stats
void			add_steps(t_core *core);
void			xp_tracker(t_core *core, int type);
void			check_stats(t_core *core);
//img create
void			add_img_anim(t_core *core);
void			add_wall_img(t_core *core);
void			add_ui_img(t_core *core);
void			add_local_img(t_core *core);
void			create_img(t_core *core, t_ui ui, void (*func)(), char *name);
void			add_img(t_core *core, char *path);
void			init_img(t_core *core);
void			print_img(t_core *core, t_vec2 pos, char *name);
void			purge_img(t_core *core);
void			compile_img(t_imgx *dest, t_imgx *imgx1, t_imgx *imgx2);
t_imgx			*get_img(t_core *core, char *name);
void			set_color(t_img *img, int adr, __uint32_t clr);
__uint32_t		get_px_adr(t_img *img, t_vec2 xy);
__uint32_t		get_px_color(t_img *img, int adr);
void			split_asset(t_core *core, t_vec3 wh, char **in);
//sound
void			playsound(char *file, int wait, int stop, int attenued);
//ui
int				draw_pause(t_core *core, int bar_rel);
void			draw_pause_cmds(t_core *core);
//game
int				get_status(t_core *core);
void			set_status(t_core *core, int status);
void			set_key_status(t_core *core, int repeat);
//player movement
void			p_can_move(t_core *core, char *map, t_vec2 xy);
void			p_move(t_core *core, int *val, int spm, int dir);
void			change_pview(t_core *core, char d);
int				p_check_zone(t_core *core, t_vec3 data, int raw);
int				check_player_bump(t_core *core, char *map, t_vec2 xy);
//build wall img
void			wall_left(t_img *img, t_ui ui);
void			wall_bottom(t_img *img, t_ui ui);
void			wall_right(t_img *img, t_ui ui);
void			wall_top(t_img *img, t_ui ui);
//test
void			browse_map(t_core *core, void (*func)());
void			browse_map_rng(t_core *core, void (*func)());
void			print_map(t_core *core, char *ent, t_vec2 px);
//anim
t_anim			*get_anim(t_core *core);
void			next_anim(t_core *core, int anim);
void			init_anim(t_core *core);
void			check_anim(t_core *core);
//
void			rupee_render(t_core *c, t_imgx *d, t_imgx *i1, t_imgx *i2);
void			check_files(void);
//centity
t_vec2			get_ent_pos(t_core *core, t_ui ui);
int				get_player_presence(t_core *core, t_vec4 mi, t_vec2 xy);

void			dodamage(t_core *core, int damage, int type);
void			death_player(t_core *core);
//
void			a_move(t_core *core, char *ent, t_vec2 ori);
void			a_print(t_core *core, char *ent, t_vec2 ori);
void			set_map_origin(t_core *core);
int				map_is_valid(t_core *core);
void			check_path(t_core *core);
int				init_map(t_core *core, char *file);
t_vec2			xopen(char *file);
void			printwallx(t_core *core, t_vec2 xy, t_vec2 num, t_vec2 max);
void			try_attack(t_core *core);
#endif