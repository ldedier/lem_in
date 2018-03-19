# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/03/19 03:20:39 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in
VISU_NAME	= lem-in_visu

CC      = gcc

PWD = \"$(shell pwd)\"

DEBUG ?= 0

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -fsanitize=address
endif

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
LIBFTDIR = libft

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX = main.c ft_parse_tools.c ft_debug.c ft_process_lem_in.c ft_parse_lem.c\
				 ft_checks.c ft_parse_phases.c ft_add_data.c ft_tools.c

VSRCS_NO_PREFIX = main_visu.c ft_init.c ft_parse_lem.c ft_parse_tools.c\
				 ft_checks.c ft_parse_phases.c ft_add_data.c ft_debug.c ft_tools.c\
				 ft_render.c ft_events.c ft_center.c ft_add_infos.c ft_stats.c\
				 ft_update_map.c ft_process_visu.c ft_visu_tools.c


SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
VSOURCES = $(addprefix $(SRCDIR)/, $(VSRCS_NO_PREFIX))

INCLUDES = $(SRCDIR)/lem_in.h $(SRCDIR)/visu_lem_in.h

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
VOBJECTS = $(addprefix $(OBJDIR)/, $(VSRCS_NO_PREFIX:%.c=%.o))

SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
SDL2_image = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
SDL2_mixer = ./frameworks/SDL2_mixer.framework/Versions/A/SDL2_mixer

all: $(BINDIR)/$(NAME) $(BINDIR)/$(VISU_NAME)

debug:
	@make all DEBUG=0

$(BINDIR)/$(NAME): $(OBJECTS)
	@make -C $(LIBFTDIR)
	@$(CC) -o $@ $^ $(CFLAGS) -L $(LIBFTDIR) -lft
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(BINDIR)/$(VISU_NAME): $(VOBJECTS)
	@make -C $(LIBFTDIR)
	@$(CC) -o $@ $^ -F ./frameworks -framework SDL2\
		-framework SDL2_image -framework SDL2_mixer -L $(LIBFTDIR) -lft -fsanitize=address
	@echo "$(OK_COLOR)$(VISU_NAME) linked with success !$(EOC)"
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(VISU_NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(VISU_NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_mixer) $(VISU_NAME)

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
