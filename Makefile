# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 23:34:13 by jnovais           #+#    #+#              #
#    Updated: 2025/10/31 20:48:48 by jnovais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLK_DIR)/libmlx.a

INCLUDES = -I$(LIBFT_DIR) -I$(MLK_DIR)

MLX_FLAGS = -L$(MLK_DIR) -lmlx -lXext -lX11 -lm

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	make all -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

norm: 
	norminette $(SRCS) *.h

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re norm
