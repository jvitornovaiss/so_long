/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:41:39 by jnovais           #+#    #+#             */
/*   Updated: 2025/12/15 19:44:35 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	img_init(t_game *game)
{
	game->img_backg = mlx_xpm_file_to_image
		(game->mlx, "images/background_green.xpm", &game->img_w, &game->img_h);
	game->img_wall = mlx_xpm_file_to_image
		(game->mlx, "images/tree_obstacle_green_bg.xpm",
			&game->img_w, &game->img_h);
	game->img_player = mlx_xpm_file_to_image
		(game->mlx, "images/naruto_key_d.xpm", &game->img_w, &game->img_h);
	game->img_colect = mlx_xpm_file_to_image
		(game->mlx, "images/scroll_collectible.xpm",
			&game->img_w, &game->img_h);
	game->img_exit = mlx_xpm_file_to_image
		(game->mlx, "images/konoha_gate_green_bg.xpm",
			&game->img_w, &game->img_h);
}

void	game_init(t_game *game)
{
	int	tile;

	tile = 64;
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	game->win = mlx_new_window(game->mlx, game->map_w * tile,
			game->map_h * tile, "so_long");
	game->moves = 0;
	game->endgame = 0;
	img_init(game);
	map_draw(game);
}
