# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshagga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 16:54:34 by mshagga           #+#    #+#              #
#    Updated: 2019/09/03 11:55:12 by mshagga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L minilibx_macos -lmlx -L ./Libft -lft -framework OpenGL -framework AppKit
IFLAGS = -I includes/ -I minilibx_macos -I ./Libft -I includes

LIBFT_DIR = ./Libft/
LIBFT = $(LIBFT_DIR)libft.a

INC = includes/fdf.h
SRC_DIR = src/
SRC_LST = main.c		\
		  init.c		\
		  controls.c	\
		  read.c		\
		  render.c		\
		  handler.c		\
		  matrix.c		\
		  colors.c		\
		  utils.c       \
		  draw_line.c   \

SOURCES = $(addprefix $(SRC_DIR), $(SRC_LST))

all: $(BIN)

$(BIN): $(LIBFT) $(SOURCES) $(INC)
	@make -C $(LIBFT_DIR)
	@$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $(BIN)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm $(BIN)

re: fclean all

