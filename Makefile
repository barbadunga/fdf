# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshagga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 16:54:34 by mshagga           #+#    #+#              #
#    Updated: 2019/07/26 13:42:29 by mshagga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L minilibx_macos -lmlx -L libft -lft -framework OpenGL -framework AppKit
IFLAGS = -I includes/ -I minilibx_macos -I libft -I includes

LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)

SRC_DIR = src/
SRC_LST = main.c init.c controls.c draw_line.c read.c render.c handler.c
SOURCES = $(addprefix $(SRC_DIR), $(SRC_LST))

all: $(BIN) $(LIBFT)

$(BIN): $(LIBFT) $(SOURCES)
	make -C $(LIBFT_DIR)
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $(BIN)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm $(BIN)

re: fclean all

