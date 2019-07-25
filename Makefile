# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshagga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 16:54:34 by mshagga           #+#    #+#              #
#    Updated: 2019/07/25 18:10:55 by mshagga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L minilibx_macos -lmlx -L libft -lft -framework OpenGL -framework AppKit
IFLAGS = -I includes/ -I minilibx_macos -I libft

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)

SRC_DIR = src/
SRC_LST = main.c
SOURCES = $(addprefix $(SRC_DIR), $(SRC_LST))

all: $(BIN)

$(BIN): $(LIBFT) $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $(BIN)