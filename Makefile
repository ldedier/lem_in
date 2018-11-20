# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 17:02:56 by ldedier           #+#    #+#              #
#    Updated: 2018/11/20 18:52:53 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in
VISU_NAME	= lem-in_visu

CC      = gcc -g3

PWD = \"$(shell pwd)\"

DEBUG ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -fsanitize=address
endif

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes

LIBFTDIR = libft
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

COMMON_NO_PREFIX =	ft_parse_lem.c ft_parse_tools.c ft_checks.c\
					ft_parse_phases.c ft_lists.c ft_tools.c ft_rooms.c\
					ft_solvable.c ft_add_link.c ft_add_room.c ft_free_turn.c

SRCS_NO_PREFIX =	main.c ft_process_lem_in.c ft_process_fill.c ft_smp.c\
					ft_mps.c ft_smp2.c ft_overlap.c ft_progress_ant.c\
					ft_deploy.c ft_print_solution.c ft_process_lem_tools.c

VSRCS_NO_PREFIX =	main_visu.c ft_init.c ft_init_sdl.c\
					ft_render.c ft_events.c ft_center.c ft_process_add_visu.c\
					ft_stats.c ft_process_visu.c ft_vant.c ft_transition.c\
					ft_parse_visu.c ft_render_ants.c ft_mouse_events.c\
					ft_render_map.c ft_render_ants_number.c ft_render_tools.c\
					ft_render_dashboard.c ft_process_events.c\
					ft_free_all_visu.c

SRCS_NO_PREFIX += $(COMMON_NO_PREFIX)
VSRCS_NO_PREFIX += $(COMMON_NO_PREFIX)

INCLUDES_NO_PREFIX = lem_in.h visu_lem_in.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
VSOURCES = $(addprefix $(SRCDIR)/, $(VSRCS_NO_PREFIX))

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
VOBJECTS = $(addprefix $(OBJDIR)/, $(VSRCS_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))
INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC)

SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
SDL2_image = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
SDL2_mixer = ./frameworks/SDL2_mixer.framework/Versions/A/SDL2_mixer
SDL2_ttf = ./frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf

all:
	@make -C $(LIBFTDIR) all
	@make $(BINDIR)/$(NAME)
	@make $(BINDIR)/$(VISU_NAME) 

debug:
	@make all DEBUG=0

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) -o $@ $^ $(CFLAGS) -L $(LIBFTDIR) -lft
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(BINDIR)/$(VISU_NAME): $(VOBJECTS) $(LIBFT)
	@$(CC) -o $@ $^ -F ./frameworks -framework SDL2\
		-framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf -L $(LIBFTDIR) -lft 
	@echo "$(OK_COLOR)$(VISU_NAME) linked with success !$(EOC)"
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(VISU_NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(VISU_NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_mixer) $(VISU_NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(VISU_NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c $< -o $@ -F ./frameworks $(CFLAGS) 

clean:
	@make clean -C $(LIBFTDIR)
	@rm -f $(OBJECTS)
	@rm -f $(VOBJECTS)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(BINDIR)/$(NAME)
	@rm -f $(BINDIR)/$(VISU_NAME)

re: fclean all

.PHONY: all clean fclean re
