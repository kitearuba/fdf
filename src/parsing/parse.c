/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/15 20:54:10 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/* FUNCTION: count_dimensions
 * ---------------------------
 * Counts the width (columns) and height (rows) of the .fdf file.
 * ************************************************************************** */
 static int	count_dimensions(int fd, t_map *map)
{
	char	*line;
	char	**split_line;
	int		width;

	map->height = 0;
	map->width = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		width = 0;
		split_line = ft_split(line, ' ');
		while (split_line[width])
			width++;
		if (map->height == 0)
			map->width = width;
		else if (width != map->width)
		{
			free_2d_array(split_line);
			free(line);
			return (0);
		}
		map->height++;
		free(line);
		free_2d_array(split_line);
	}
	if (map->height == 0 || map->width == 0)
		return (0);
	return (1);
}

/* ************************************************************************** */
/* FUNCTION: parse_map
 * --------------------
 * Parses the .fdf file and stores the data into a t_map structure.
 * ************************************************************************** */
t_map	*parse_map(const char *filename)
{
	int		fd;
	int		row;
	int		col;
	char	*line;
	char	**split_line;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (!count_dimensions(fd, map))
	{
		free(map);
		close(fd);
		return (NULL);
	}
	close(fd);

	map->grid = malloc(sizeof(int *) * map->height);
	if (!map->grid)
	{
		free(map);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
 	if (fd < 0)
 	{
 		free(map->grid);
 		free(map);
 		return (NULL);
 	}
 	// Parse the map and populate the grid
	row = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		split_line = ft_split(line, ' ');
		map->grid[row] = malloc(sizeof(int) * map->width);
		if (!map->grid[row])
		{
			free(line);
			free_2d_array(split_line);
			while (row-- > 0)
			{
				row--;
				free(map->grid[row]);
			}
			free(map->grid);
			free(map);
			close(fd);
			return (NULL);
		}
		col = 0;
		while (col < map->width)
		{
			map->grid[row][col] = parse_strict_atoi(split_line[col], split_line);
			col++;
		}
		free(line);
		free_2d_array(split_line);
		row++;
	}
	close(fd);
	return (map);
}


/*
	split_args = ft_split(argv[1], ' ');
	if (!split_args || !*split_args)
	{
		if (split_args)
			free_2d_array(split_args);
		fatal_error();
	}
	index = 0;
	while (split_args[index])
	{
		parsed_value = parse_strict_atoi(split_args[index], &a, split_args);
		add_to_stack(&a, stack_new(parsed_value));
		index++;
	}
	free_2d_array(split_args);
	return (a);
}
*/