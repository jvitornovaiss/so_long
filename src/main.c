/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:01:18 by jnovais           #+#    #+#             */
/*   Updated: 2025/12/27 19:30:34 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_ber(char *argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	i -= 1;
	if (argv[i - 3] == '.' && argv[i - 2] == 'b' && argv[i - 1] == 'e'
		&& argv[i] == 'r')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(1, "Error: invalid parameter\n", 26);
		return (1);
	}
	game.map = read_map(argv[1]);
	if (game.map && is_ber(argv[1]) && map_checker(&game))
	{
		game_init(&game);
		gameplay(&game);
		mlx_loop(game.mlx);
	}
	else
	{
		if (game.map)
			free_map(game.map);
		write(2, "Error: Invalid Map\n", 18);
	}
	return (0);
}
