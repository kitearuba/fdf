/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/fdf.h"

int main(int argc, char **argv)
{
	t_map *map;
	int i;
	int j;

	if (argc != 2)
	{
		ft_printf_fd(STDERR, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		ft_printf_fd(STDERR, "Error: Failed to parse map.\n");
		return (1);
	}
	ft_printf("Map Dimensions: %d x %d\n", map->height, map->width);

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%d ", map->grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	// Free the map
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
	return (0);
}
