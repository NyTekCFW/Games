# Styles de texte
COLOR_RESET = \033[0m
COLOR_BOLD = \033[1m
COLOR_DIM = \033[2m
COLOR_UNDERLINE = \033[4m
COLOR_BLINK = \033[5m
COLOR_REVERSE = \033[7m
COLOR_HIDDEN = \033[8m

# Couleurs du texte (texte / fond)
COLOR_BLACK = \033[30m
COLOR_RED = \033[31m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_BLUE = \033[34m
COLOR_MAGENTA = \033[35m
COLOR_CYAN = \033[36m
COLOR_WHITE = \033[37m

# Couleurs de fond
COLOR_BG_BLACK = \033[40m
COLOR_BG_RED = \033[41m
COLOR_BG_GREEN = \033[42m
COLOR_BG_YELLOW = \033[43m
COLOR_BG_BLUE = \033[44m
COLOR_BG_MAGENTA = \033[45m
COLOR_BG_CYAN = \033[46m
COLOR_BG_WHITE = \033[47m

# Styles de texte supplémentaires
COLOR_BOLD_BRIGHT = \033[1;1m
COLOR_DIM_BRIGHT = \033[2;2m
COLOR_UNDERLINE_BRIGHT = \033[4;4m
COLOR_BLINK_BRIGHT = \033[5;5m
COLOR_REVERSE_BRIGHT = \033[7;7m
COLOR_HIDDEN_BRIGHT = \033[8;8m

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lX11 -lXext
RM = rm -rf
NAME = so_long
MLX_DIR = ./minilibx-linux/
OBJ_DIR = obj
SAVE_DIR = saves
MLX = $(MLX_DIR)libmlx_Linux.a

SRC_DIR = ./src/
CM_DIR = $(SRC_DIR)cmd/
MP_DIR = $(SRC_DIR)mapping/
SV_DIR = $(SRC_DIR)savedata/
UI_DIR = $(SRC_DIR)ui/
UT_DIR = $(SRC_DIR)utils/
WM_DIR = $(SRC_DIR)window/
SY_DIR = $(SRC_DIR)system/
IM_DIR = $(SRC_DIR)img/
GM_DIR = $(SRC_DIR)game/

CM_FL = $(CM_DIR)cmd_func_0.c \
		$(CM_DIR)cmd_func_1.c \
		$(CM_DIR)cmd_flags.c \
		$(CM_DIR)cmd_scripts.c

GM_FL = $(GM_DIR)game.c \
		$(GM_DIR)sound.c \
		$(GM_DIR)p_attack.c \
		$(GM_DIR)p_movement_0.c \
		$(GM_DIR)p_movement_1.c \
		$(GM_DIR)p_movement_2.c \
		$(GM_DIR)axis_movement.c \
		$(GM_DIR)centity.c \
		$(GM_DIR)corrupt_0.c \
		$(GM_DIR)anim.c \
		$(GM_DIR)map.c

IM_FL = $(IM_DIR)img_base.c \
		$(IM_DIR)img_create.c \
		$(IM_DIR)img_build.c \
		$(IM_DIR)img_edit.c \
		$(IM_DIR)img_add.c \
		$(IM_DIR)img_add_walls.c \
		$(IM_DIR)img_add_anim.c \
		$(IM_DIR)img_split.c

MP_FL = $(MP_DIR)map_solver.c \
		$(MP_DIR)map_check.c \
		$(MP_DIR)map_init.c

SV_FL = $(SV_DIR)savedata.c \
		$(SV_DIR)stats.c

UI_FL = $(UI_DIR)ui_submenu.c \
		$(UI_DIR)ui_draw_0.c \
		$(UI_DIR)ui_draw_1.c \
		$(UI_DIR)ui_button.c \
		$(UI_DIR)ui_leaderboards.c \
		$(UI_DIR)ui_pause.c \
		$(UI_DIR)ui_player.c \
		$(UI_DIR)ui_wall.c \
		$(UI_DIR)ui_info.c \
		$(UI_DIR)ui_print_wall.c \
		$(UI_DIR)ui_map.c
		

UT_FL = $(UT_DIR)memory.c \
		$(UT_DIR)string_0.c \
		$(UT_DIR)string_1.c \
		$(UT_DIR)string_2.c \
		$(UT_DIR)math.c \
		$(UT_DIR)gnl.c \
		$(UT_DIR)shortcuts_0.c \
		$(UT_DIR)shortcuts_1.c \
		$(UT_DIR)shortcuts_2.c \
		$(UT_DIR)vector.c \
		$(UT_DIR)color.c \
		$(UT_DIR)itoa.c \
		$(UT_DIR)xopen.c

WM_FL = $(WM_DIR)win_main.c \
		$(WM_DIR)win_hook.c \
		$(WM_DIR)win_hookr.c \
		$(WM_DIR)win_exit.c \
		$(WM_DIR)win_cfg.c \
		$(WM_DIR)win_cfg_exec.c \
		$(WM_DIR)win_cfg_apply.c \
		$(WM_DIR)win_binds.c

SRCS = $(SRC_DIR)main.c $(CM_FL) $(GM_FL) $(IM_FL) $(MP_FL) $(SV_FL) $(UI_FL) $(UT_FL) $(WM_FL)

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

vpath %.c $(SRC_DIR) $(GM_DIR) $(CM_DIR) $(IM_DIR) $(MP_DIR) $(SV_DIR) $(UI_DIR) $(UT_DIR) $(WM_DIR)

all: init_header $(OBJ_DIR) $(SAVE_DIR) $(NAME)

$(NAME): $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFLAGS) -lm
	@echo "$(COLOR_BOLD)$(COLOR_MAGENTA)Compilation done.$(COLOR_RESET)"
	@echo ""

$(SAVE_DIR):
	@echo "$(COLOR_CYAN)Creating directory $(SAVE_DIR)$(COLOR_RESET)"
	@mkdir -p $(SAVE_DIR)

$(OBJ_DIR):
	@echo "$(COLOR_CYAN)Creating directory $(OBJ_DIR)$(COLOR_RESET)"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ || (rm -f $@; exit 1)
	@printf "$(COLOR_BOLD)$(COLOR_CYAN)Compile %-30s ➜$(COLOR_RESET) $(COLOR_BOLD)$(COLOR_GREEN) %-30s$(COLOR_RESET) $(OK_COLOR)[✓]$(NO_COLOR)\n" $(notdir $<) $(notdir $@)

$(MLX):
	@echo "$(COLOR_YELLOW)Creating libmlx...$(COLOR_RESET)"
	@chmod 777 $(MLX_DIR)configure
	@make -s -C $(MLX_DIR)

clean:
	@$(RM) $(OBJS)
	@echo "$(COLOR_BOLD)$(COLOR_YELLOW)All .o files removed.$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(COLOR_BOLD)$(COLOR_YELLOW)$(NAME) removed.$(COLOR_RESET)"

re: fclean all

init_header: 
	@clear
	@echo ".-----------------."
	@echo "| .--------------. |"
	@echo "| | ____  _____  | |"
	@echo "| ||_   \|_   _| | |"
	@echo "| |  |   \ | |   | |"
	@echo "| |  | |\ \| |   | |"
	@echo "| | _| |_\   |_  | |"
	@echo "| ||_____|\____| | |"
	@echo "| |              | |"
	@echo "| '--------------' |"
	@echo " '----------------' "
	@echo ""
