/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:27:34 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	allocate_map_memory(t_map *map)
{
	int	i;

	map->data = (int **)malloc(map->height * sizeof(int *));
	if (!map->data)
		return (0);

	i = 0;
	while (i < map->height)
	{
		map->data[i] = (int *)malloc(map->width * sizeof(int));  // Allocate max width
		if (!map->data[i])
		{
			free_map(map);
			return (0);
		}
		ft_memset(map->data[i], 0, map->width * sizeof(int));
		i++;
	}
	return (1);
}

static int	count_dimensions(const char *filename, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!validate_dimensions(line, map))
		{
			ft_printf_fd(STDERR, "Error: Inconsistent row length\n");
			free(line);
			close(fd);
			return (0);
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
static int	parse_values(const char *filename, t_map *map)
{
	int	fd;
	int	row;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	row = 0;
	if (!parse_rows(fd, map, &row))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	parse_map(const char *filename, t_map *map)
{
	if (!count_dimensions(filename, map))
	{
		ft_printf_fd(STDERR, "Error: Failed to count map dimensions\n");
		return (0);
	}
	if (!allocate_map_memory(map))
	{
		ft_printf_fd(STDERR, "Error: Memory allocation failed\n");
		return (0);
	}
	if (!parse_values(filename, map))
	{
		ft_printf_fd(STDERR, "Error: Failed to parse map values\n");
		free_map(map);
		return (0);
	}
	return (1);
}
