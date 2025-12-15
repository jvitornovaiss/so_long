/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>             +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:30:37 by jnovais            #+#    #+#            */
/*   Updated: 2025/12/12 09:30:37 by jnovais           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_height(char **map)
{
	int h = 0;
	while (map[h])
		h++;
	return (h);
}
static int	get_width(char **map)
{
	return ft_strlen(map[0]);
}
static char	**dup_map(char **map)
{
	int		h = get_height(map);
	char	**copy = malloc(sizeof(char *) * (h + 1));
	int		i = 0;

	if (!copy)
		return (NULL);

	while (i < h)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
static void	flood_fill(char **map, int row, int col, int height, int width)
{
	if (row < 0 || col < 0 || row >= height || col >= width)
		return;

	if (map[row][col] == '1' || map[row][col] == 'F')
		return;

	if (map[row][col] == 'E') // não entra na saída
		return;

	map[row][col] = 'F';

	flood_fill(map, row + 1, col, height, width);
	flood_fill(map, row - 1, col, height, width);
	flood_fill(map, row, col + 1, height, width);
	flood_fill(map, row, col - 1, height, width);
}
static int	collectibles_reachable(char **map)
{
	int y = 0;
	int x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
static int	exit_is_reachable(char **map, int height, int width)
{
	int y = 0;
	int x;

	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'E')
			{
				// saída deve ter um F do lado
				if (y + 1 < height && map[y + 1][x] == 'F') return (1);
				if (y - 1 >= 0     && map[y - 1][x] == 'F') return (1);
				if (x + 1 < width  && map[y][x + 1] == 'F') return (1);
				if (x - 1 >= 0     && map[y][x - 1] == 'F') return (1);

				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}
int	check_reachable(t_game *game)
{
	char	**copy = dup_map(game->map);
	int		height = get_height(game->map);
	int		width = get_width(game->map);
	int		ok = 1;

	if (!copy)
		return (0);

	// flood fill a partir do player
	flood_fill(copy, game->y_player, game->x_player, height, width);

	// verifica C
	if (!collectibles_reachable(copy))
		ok = 0;

	// verifica E
	if (!exit_is_reachable(copy, height, width))
		ok = 0;

	free_map(copy);
	if (ok == 0)
		write(2, "Exit not is possible\n", 22);
	return (ok);
}
