# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 02:23:01 by dmoliner          #+#    #+#              #
#    Updated: 2023/11/16 02:23:44 by dmoliner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol

SRCDIR	= ./source
HEADDIR	= ./header
OBJDIR	= ./.obj
FTDIR	= ./libft
MLXDIR	= ./MLX42
MLXLIB	= ./$(MLXDIR)/libmlx42.a

SRC		= main.c
OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -I $(HEADDIR) -lglfw -L"/Users/$(id -un)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all: obj $(FT) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $< $(MLXLIB) $(CFLAGS) -o $@

$(NAME): $(OBJ)
	echo Hola

clean:
	rm -rf $(OBJDIR)
	make -C $(FTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all
