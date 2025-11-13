/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:01:18 by jnovais           #+#    #+#             */
/*   Updated: 2025/11/13 20:45:07 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "mlx.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	draw_map(void *mlx, void *win, char **map)
{
	int	y = 0;
	int	x;
	int	tile_size = 64; // cada quadradinho 64x64 pixels

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1') // parede
				mlx_pixel_put(mlx, win, x * tile_size, y * tile_size, 0x00444444);
			else if (map[y][x] == '0') // chão
				mlx_pixel_put(mlx, win, x * tile_size, y * tile_size, 0x00AAAAAA);
			else if (map[y][x] == 'P') // player (verde)
				mlx_pixel_put(mlx, win, x * tile_size, y * tile_size, 0x0000FF00); 
			else if (map[y][x] == 'C') // coletável (amarelo)
				mlx_pixel_put(mlx, win, x * tile_size, y * tile_size, 0x00FFFF00);
			else if (map[y][x] == 'E') // saída (vermelho)
				mlx_pixel_put(mlx, win, x * tile_size, y * tile_size, 0x00FF0000);
			x++;
		}
		y++;
	}
}

char	**red_map(char *path)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * 100);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while ((line != NULL))
	{
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	char	**map;

	map = red_map("maps/mapa.txt");
	if (!map)
	{
		perror("map error");
		return (1);
	}
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "so_long test");
	draw_map(mlx, win, map);
	mlx_hook(win, 17, 0, close_window, NULL);
	mlx_loop(mlx);
	return (0);
}
