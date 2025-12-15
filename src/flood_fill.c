/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flod_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:05:27 by jnovais           #+#    #+#             */
/*   Updated: 2025/12/15 20:09:04 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, t_fill f)
{
	if (f.y < 0 || f.x < 0 || f.y >= f.height || f.x >= f.width)
		return ;
	if (map[f.y][f.x] == '1' || map[f.y][f.x] == 'F')
		return ;
	if (map[f.y][f.x] == 'E')
		return ;
	map[f.y][f.x] = 'F';
	flood_fill(map, (t_fill){f.y + 1, f.x, f.height, f.width});
	flood_fill(map, (t_fill){f.y - 1, f.x, f.height, f.width});
	flood_fill(map, (t_fill){f.y, f.x + 1, f.height, f.width});
	flood_fill(map, (t_fill){f.y, f.x - 1, f.height, f.width});
}

static int	collectibles_reachable(char **map)
{
	int	y;
	int	x;

	y = 0;
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
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'E')
			{
				if ((y + 1 < height && map[y + 1][x] == 'F')
					|| (y - 1 >= 0 && map[y - 1][x] == 'F')
					|| (x + 1 < width && map[y][x + 1] == 'F')
					|| (x - 1 >= 0 && map[y][x - 1] == 'F'))
					return (1);
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
	char	**copy;
	int		ok;
	t_fill	f;

	copy = dup_map(game->map);
	if (!copy)
		return (0);
	ok = 1;
	f.y = game->y_player;
	f.x = game->x_player;
	f.height = get_height(game->map);
	f.width = ft_strlen(game->map[0]);
	flood_fill(copy, f);
	if (!collectibles_reachable(copy))
		ok = 0;
	if (!exit_is_reachable(copy, f.height, f.width))
		ok = 0;
	free_map(copy);
	if (ok == 0)
		write(2, "Exit not is possible\n", 22);
	return (ok);
}