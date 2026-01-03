/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:04:03 by jnovais           #+#    #+#             */
/*   Updated: 2025/12/27 19:20:50 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_cell(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'P')
	{
		game->n_player++;
		game->y_player = y;
		game->x_player = x;
	}
	else if (game->map[y][x] == 'C')
		game->n_colect++;
	else if (game->map[y][x] == 'E')
		game->n_exit++;
}

void	init_map_info(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->n_colect = 0;
	game->n_exit = 0;
	game->n_player = 0;
	game->map_h = 0;
	game->map_w = ft_strlen(game->map[0]);
	while (game->map[game->map_h])
		game->map_h++;
	while (y < game->map_h)
	{
		x = 0;
		while (game->map[y][x])
		{
			process_cell(game, y, x);
			x++;
		}
		y++;
	}
}
