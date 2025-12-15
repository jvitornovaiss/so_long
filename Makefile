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

NAME        = so_long

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
RM          = rm -f

SRCS = \
	src/main.c \
	src/end_game.c \
	src/map_check.c \
	src/map_check_flod_fill.c \
	src/read_map.c \
	src/init_map_info.c \
	src/init_game.c \
	src/draw_game.c \
	src/gameplay.c \
	src/player_new.c

OBJS        = $(SRCS:.c=.o)

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX         = $(MLX_DIR)/libmlx.a

INCLUDES    = -I$(LIBFT_DIR) -I$(MLX_DIR)

MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -no-pie -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
	norminette $(SRCS) *.h

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re norm
