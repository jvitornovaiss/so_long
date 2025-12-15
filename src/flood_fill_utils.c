/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flod_fill_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:05:30 by jnovais           #+#    #+#             */
/*   Updated: 2025/12/15 20:11:48 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_height(char **map)
{
	int	h;

	h = 0;
	while (map[h])
		h++;
	return (h);
}

char	**dup_map(char **map)
{
	int		h;
	char	**copy;
	int		i;

	h = get_height(map);
	copy = malloc(sizeof(char *) * (h + 1));
	if (!copy)
		return (NULL);
	i = 0;
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
