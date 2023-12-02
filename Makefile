# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 13:12:12 by dmoliner          #+#    #+#              #
#    Updated: 2023/12/03 00:09:11 by dmoliner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR := ./source
PRINTF_DIR := ./printf
LIBFT_DIR := ./libft

BUILD_DIR := ./build

SRCS =	ft_check_apollonian.c \
		ft_check_julia.c \
		ft_check_mandelbrot.c \
		ft_input_hooks.c \
		ft_close_task.c \
		ft_render.c \
		ft_render_utils.c \
		main.c

PRINTFSRCS =	ft_printf.c \
				print_char.c \
				print_hex.c \
				print_int.c \
				print_ptr.c \
				print_str.c \
				print_uint.c

LIBFTSRCS =	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

FRACTOL_NAME = fractol
FRACTOL_FILE = main.c
NAME = libftprintf.a
CC = gcc
AR = ar -rcs
CFLAGS := -c -Wall -Wextra -Werror
LDFLAGS := -L . -lftprintf

# Object files
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
PRINTFOBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(PRINTFSRCS))
LIBOBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(LIBFTSRCS))

# Phony targets
.PHONY: all clean fclean re
# Default
all: ${NAME} $(FRACTOL_NAME)

# Linking the library
$(NAME): $(PRINTFOBJS) $(LIBOBJS) Makefile
	$(AR) $@ $(PRINTFOBJS) $(LIBOBJS)

$(FRACTOL_NAME): $(OBJS) $(NAME) Makefile
	$(CC) -g $(OBJS) -fsanitize=address -L . -lftprintf -lmlx -framework OpenGL -framework AppKit -o $(FRACTOL_NAME)

# Build targets
$(BUILD_DIR)/%.o: $(PRINTF_DIR)/%.c | $(BUILD_DIR) Makefile
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(LIBFT_DIR)/%.c | $(BUILD_DIR) Makefile
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR) Makefile
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Cleaning
clean :
	rm -rf $(PRINTFOBJS) $(LIBOBJS) $(OBJS)

fclean : clean
	rm -f $(NAME) ${FRACTOL_NAME}

re : fclean all
