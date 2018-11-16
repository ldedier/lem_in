# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/11/16 18:33:09 by ldedier          ###   ########.fr        #
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

LIBSDL2DIR = ~/.brew/lib
LIBSDL2_INCLUDEDIR = ~/.brew/Cellar/sdl2/2.0.8/include/SDL2/
LIBSDL2TTF_INCLUDEDIR = ~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2/
LIBSDL2NET_INCLUDEDIR = ~/.brew/Cellar/sdl2_net/2.0.1/include/SDL2/
LIBSDL2MIXER_INCLUDEDIR = ~/.brew/Cellar/sdl2_mixer/2.0.2_3/include/SDL2/
LIBSDL2IMAGE_INCLUDEDIR =  ~/.brew/Cellar/sdl2_image/2.0.3/include/SDL2/

LIBSDL2DIR_MB = /usr/local/lib
LIBSDL2_INCLUDEDIR_MB = /usr/local/Cellar/sdl2/2.0.8/include/SDL2/
LIBSDL2TTF_INCLUDEDIR_MB = /usr/local/Cellar/sdl2_ttf/2.0.14/include/SDL2/
LIBSDL2IMAGE_INCLUDEDIR_MB = /usr/local/Cellar/sdl2_image/2.0.3/include/SDL2/
LIBSDL2NET_INCLUDEDIR_MB = /usr/local/Cellar/sdl2_net/2.0.1/include/SDL2/
LIBSDL2MIXER_INCLUDEDIR_MB = /usr/local/Cellar/sdl2_mixer/2.0.2_3/include/SDL2/

SRCS_NO_PREFIX = main.c ft_parse_tools.c ft_debug.c ft_process_lem_in.c\
				 ft_parse_lem.c ft_checks.c ft_parse_phases.c ft_add_data.c\
				 ft_tools.c ft_lists.c ft_rooms.c

VSRCS_NO_PREFIX = main_visu.c ft_init.c ft_parse_lem.c ft_parse_tools.c\
				  ft_checks.c ft_parse_phases.c ft_add_data.c ft_debug.c\
				  ft_tools.c  ft_render.c ft_events.c ft_center.c ft_add_infos.c\
				  ft_stats.c ft_process_visu.c ft_visu_tools.c ft_lists.c\
				  ft_rooms.c

INCLUDES_NO_PREFIX = lem_in.h visu_lem_in.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
VSOURCES = $(addprefix $(SRCDIR)/, $(VSRCS_NO_PREFIX))

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
VOBJECTS = $(addprefix $(OBJDIR)/, $(VSRCS_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))
INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)

ifeq ($(MACBOOK), 1)
	INC +=  -I $(LIBSDL2_INCLUDEDIR_MB)\
			-I $(LIBSDL2TTF_INCLUDEDIR_MB)\
			-I $(LIBSDL2NET_INCLUDEDIR_MB)\
			-I $(LIBSDL2MIXER_INCLUDEDIR_MB)\
			-I $(LIBSDL2IMAGE_INCLUDEDIR_MB)
else
	INC +=  -I $(LIBSDL2_INCLUDEDIR)\
			-I $(LIBSDL2TTF_INCLUDEDIR)\
			-I $(LIBSDL2NET_INCLUDEDIR)\
			-I $(LIBSDL2MIXER_INCLUDEDIR)\
			-I $(LIBSDL2IMAGE_INCLUDEDIR)
endif

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC)

ifeq ($(DEBUG), 1)
	CFLAGS += -g -DDEBUG -fsanitize=address
else
	CFLAGS += -Ofast
endif

LFLAGS = -L $(LIBFTDIR) -lft

ifeq ($(MACBOOK), 1)
	LFLAGS += -L $(LIBSDL2DIR_MB)
else
	LFLAGS += -L $(LIBSDL2DIR)
endif

LFLAGS += -lsdl2 -lsdl2_ttf -lsdl2_mixer -lsdl2_image

opti:
	@make -j all

all:
	@make -C $(LIBFTDIR) all
	@make $(BINDIR)/$(NAME)
	@make $(BINDIR)/$(VISU_NAME) 

macbook:
	@make -j all MACBOOK=1

debug:
	@make all DEBUG=0

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) -o $@ $^ -L $(LIBFTDIR) -lft 
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(BINDIR)/$(VISU_NAME): $(VOBJECTS) $(LIBFT)
	@$(CC) -o $@ $^ $(LFLAGS) -fsanitize=address
	@echo "$(OK_COLOR)$(VISU_NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c $< -o $@ $(CFLAGS) 

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
