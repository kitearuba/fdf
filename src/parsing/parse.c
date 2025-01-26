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

static int	ft_str_is_whitespace(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n'
			&& *str != '\v' && *str != '\f' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}

/* ************************************************************************** */
/* FUNCTION: count_dimensions
 * ---------------------------
 * Counts the width (columns) and height (rows) of the .fdf file.
 * ************************************************************************** */
static int count_dimensions(int fd, t_map *map)
{
    char    *line;
    char    **split_line;
    int     width;

    map->height = 0;
    map->width = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        ft_printf("Reading line: '%s'\n", line); // Debug

        // Skip empty or whitespace-only lines
        if (line == NULL || *line == '\0' || ft_str_is_whitespace(line))
        {
            ft_printf("Skipping empty/whitespace-only line.\n");
            free(line);
            continue;
        }

        width = 0;
        split_line = ft_split(line, ' ');
        if (!split_line || !split_line[0]) // Handle invalid splits
        {
            ft_printf("Skipping invalid split for line: '%s'\n", line);
            free_2d_array(split_line);
            free(line);
            continue;
        }

        while (split_line[width])
        {
            ft_printf("Split value: '%s'\n", split_line[width]);
            width++;
        }

        if (map->height == 0)
            map->width = width;
        else if (width != map->width) // Mismatched widths
        {
            ft_printf("Width mismatch: Expected %d, Found %d\n", map->width, width);
            free_2d_array(split_line);
            free(line);
            close(fd);
            return (0);
        }

        map->height++;
        free(line);
        free_2d_array(split_line);
    }

    if (map->height == 0 || map->width == 0)
    {
        ft_printf("No valid rows found. Height: %d, Width: %d\n", map->height, map->width);
        return (0);
    }

    ft_printf("Final Dimensions: Height = %d, Width = %d\n", map->height, map->width);
    return (1);
}

/* ************************************************************************** */
/* FUNCTION: parse_map                                                        */
/* Parses the .fdf file and stores the data into a t_map structure.           */
/* ************************************************************************** */
t_map *parse_map(const char *filename)
{
    int     fd;
    int     row;
    int     col;
    char    *line;
    char    **split_line;
    t_map   *map;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_printf_fd(STDERR, "Error: Cannot open file %s\n", filename);
        return (NULL);
    }

    map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->height = 0;
    map->width = 0;

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

    row = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line == NULL || *line == '\0' || ft_str_is_whitespace(line))
        {
            ft_printf("Skipping empty/whitespace-only line.\n");
            free(line);
            continue;
        }

        ft_printf("Reading line: '%s'\n", line); // Debug
        split_line = ft_split(line, ' ');
        if (!split_line || !split_line[0])
        {
            ft_printf("Skipping invalid split for line: '%s'\n", line);
            free_2d_array(split_line);
            free(line);
            continue;
        }

        map->grid[row] = malloc(sizeof(int) * map->width);
        if (!map->grid[row])
        {
            free(line);
            free_2d_array(split_line);
            while (row-- > 0)
                free(map->grid[row]);
            free(map->grid);
            free(map);
            close(fd);
            return (NULL);
        }

        col = 0;
        while (col < map->width)
        {
            ft_printf("Converting value: '%s'\n", split_line[col]); // Debug
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
