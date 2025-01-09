#/* ************************************************************************** */
#/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
#/*                                                                            */
#/*   Makefile                                                                 */
#/*                                                                            */
#/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
#/*                                                                            */
#/*   Created: 09/12/2024 07:08:08 by NyTekCFW                                 */
#/*   Updated: 09/12/2024 09:10:57 by NyTekCFW                                 */
#/*                                                                            */
#/* ************************************************************************** */

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

# Vérification de l'environnement
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

# Inclusion des règles GBA
include $(DEVKITARM)/gba_rules

# Variables principales
PROJECT_NAME := Game_Engine
OBJ_DIR      := obj
PROJECT_SRC  := game game/src $(addprefix game/src/, engine textures bgame submenu)
PROJECT_INC  := game game/includes
COREGBA_SRC  := coregba coregba/src $(addprefix coregba/src/, utils keys graphics_context graphics tasks savedata system)
COREGBA_INC  := coregba/includes
SOURCES      := $(COREGBA_SRC) $(PROJECT_SRC)
INCLUDES     := $(COREGBA_INC) $(PROJECT_INC)
DATA         :=
MUSIC        :=
OBJCOPY      := arm-none-eabi-objcopy
OBJSTRIP     := arm-none-eabi-strip

# Options de compilation
ARCH        := -mthumb -mthumb-interwork
CXXFLAGS    := -g -Wall -O3 -Xlinker -Wl,-Map=output.map -mcpu=arm7tdmi \
                -mtune=arm7tdmi $(ARCH) $(INCLUDE) -fno-rtti -fno-exceptions
ASFLAGS     := -g $(ARCH)
LDFLAGS     := -g $(ARCH) -Wl,-Map,$(notdir $(PROJECT_NAME).map)
LIBS        := -lmm -lgba
LIBDIRS     := $(LIBGBA)

# Configuration des chemins
ifneq ($(OBJ_DIR),$(notdir $(CURDIR)))

export OUTPUT := $(CURDIR)/$(PROJECT_NAME)
export VPATH  := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                 $(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
                 $(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(OBJ_DIR)

#silent build
export V := 1

# Gestion des fichiers
CFILES       := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES     := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES       := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES     := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

ifneq ($(strip $(MUSIC)),)
	export AUDIOFILES := $(foreach dir,$(notdir $(wildcard $(MUSIC)/*.*)),$(CURDIR)/$(MUSIC)/$(dir))
	BINFILES += soundbank.bin
endif

ifeq ($(strip $(CPPFILES)),)
	export LD := $(CC)
else
	export LD := $(CXX)
endif

export OFILES_BIN := $(addsuffix .o,$(BINFILES))
export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)
export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE := $(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
                  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                  -I$(CURDIR)/$(OBJ_DIR)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)


# Règles principales
.PHONY: $(OBJ_DIR) clean re

$(OBJ_DIR):
	@printf "$(COLOR_CYAN)Creating directory $(OBJ_DIR)$(COLOR_RESET)\n"
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(OBJ_DIR) -f $(CURDIR)/Makefile

re: clean $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)/*
	@rm -fr $(PROJECT_NAME).elf $(PROJECT_NAME).gba
	@printf "$(COLOR_BOLD)$(COLOR_YELLOW)All .o files and build removed.$(COLOR_RESET)\n"

else

# Règles de génération des binaires
$(OUTPUT).gba: $(OUTPUT).elf
#	@$(OBJSTRIP) --strip-all $(OUTPUT).elf
	@$(OBJCOPY) -O binary $(OUTPUT).elf $(OUTPUT).gba
	@printf "$(COLOR_BOLD)$(COLOR_MAGENTA)Compilation done.$(COLOR_RESET)\n"
#	@mgba-qt $(OUTPUT).gba > /dev/null 2>&1

$(OUTPUT).elf: $(OFILES)

$(OFILES_SOURCES): $(HFILES)

soundbank.bin soundbank.h: $(AUDIOFILES)
	@mmutil $^ -osoundbank.bin -hsoundbank.h

%.bin.o %_bin.h: %.bin
	@echo $(notdir $<)
	@$(bin2o)

# Inclusion des dépendances
-include $(DEPSDIR)/*.d

endif
