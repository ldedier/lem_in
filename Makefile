# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/03/01 23:08:45 by ldedier          ###   ########.fr        #
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

SRCS_NO_PREFIX = main.c

VSRCS_NO_PREFIX = main_visu.c

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
VSOURCES = $(addprefix $(SRCDIR)/, $(VSRCS_NO_PREFIX))

INCLUDES = $(SRCDIR)/lem_in.h $(SRCDIR)/visu_lem_in.h

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
VOBJECTS = $(addprefix $(OBJDIR)/, $(VSRCS_NO_PREFIX:%.c=%.o))

all: $(BINDIR)/$(NAME) $(BINDIR)/$(VISU_NAME)

debug:
	@make all DEBUG=1

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c $< -o $@ $(CFLAGS) 

$(BINDIR)/$(NAME): $(OBJECTS)
	@make -C $(LIBFTDIR)
	@$(CC) -o $@ $^ $(CFLAGS) -L $(LIBFTDIR) -lft
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(BINDIR)/$(VISU_NAME): $(VOBJECTS)
	@make -C $(LIBFTDIR)
	@$(CC) -o $@ $^ $(CFLAGS) -L $(LIBFTDIR) -lft -lmlx -framework OpenGL -framework Appkit
	@echo "$(OK_COLOR)$(VISU_NAME) linked with success !$(EOC)"

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
