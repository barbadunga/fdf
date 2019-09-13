# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshagga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 16:54:34 by mshagga           #+#    #+#              #
#    Updated: 2019/09/13 12:28:20 by mshagga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx_macos/
LIBFT_DIR = ./Libft/
OBJ_DIR = ./objects/
SRC_DIR = ./sources/
INC_DIR = ./includes/
INC_LST = fdf.h \

LIBFT = $(LIBFT_DIR)libft.a
INC = $(addprefix $(INC_DIR), $(INC_LST))
MLX = $(MLX_DIR)libmlx.a

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

OBJ_LST = $(patsubst %.c, %.o, $(SRC_LST))

IFLAGS = -I $(INC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR)
LFLAGS = -L $(MLX_DIR) -lmlx -L $(LIBFT_DIR) -lft -framework OpenGL -framework Appkit

SRC = $(addprefix $(SRC_DIR), $(SRC_LST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LST))

all: $(BIN)

$(BIN): $(OBJ) $(LIBFT) $(INC) $(MLX)
	echo "make BIN"
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $(BIN) $(OBJ)

$(OBJ_DIR)%.o: $(SRC)%.c $(INC)
	echo "make OBJ"
	mkdir -p objects
	$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@

$(LIBFT):
	echo "make LIB"
	make -sC $(LIBFT_DIR)

$(MLX):
	echo "make MLX"
	make -sC $(MLX_DIR)

clean:
	make clean -sC $(LIBFT_DIR)
	make clean -sC $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	make fclean -sC $(LIBFT_DIR)
	make fclean -sC $(MLX_DIR)
	rm $(BIN)

re: fclean all

