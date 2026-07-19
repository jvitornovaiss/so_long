/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 11:45:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/16 23:15:00 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void	print_color(char *name, t_color color)
{
	printf("%s: RGB(%d, %d, %d) | hex: 0x%06X\n", name, color.r,
		color.g, color.b, color.hex);
}

static void	print_grid(char **grid)
{
	int	y;

	y = 0;
	while (grid[y])
	{
		printf("|%s|\n", grid[y]);
		y++;
	}
}

static void	print_map_data(t_map_data *map)
{
	printf("\n--- Parsed map data ---\n");
	printf("NO texture: %s\nSO texture: %s\n", map->no_texture,
		map->so_texture);
	printf("WE texture: %s\nEA texture: %s\n", map->we_texture,
		map->ea_texture);
	print_color("Floor", map->floor_color);
	print_color("Ceiling", map->ceiling_color);
	printf("Map size: %d x %d\n", map->map_width, map->map_height);
	printf("Player: (%d, %d), direction: %c\n", map->player_start_x,
		map->player_start_y, map->player_dir);
	printf("Map grid:\n");
	print_grid(map->map_grid);
	printf("-----------------------\n\n");
}

int	main(int argc, char **argv)
{
	t_map_data	*map;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	map = parse_cub_file(argv[1]);
	if (!map)
	{
		write(2, "Error\nInvalid .cub file\n", 25);
		return (1);
	}
	print_map_data(map);
	write(1, "Map parsed and validated successfully.\n", 39);
	free_map_data(map);
	return (0);
}
