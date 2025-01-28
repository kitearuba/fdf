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
#include <string.h> // For memset

static int allocate_map_memory(t_map *map)
{
    int i;

    map->data = (int **)malloc(map->height * sizeof(int *));
    if (!map->data)
        return (0);
    i = 0;
    while (i < map->height)
    {
        map->data[i] = (int *)malloc(map->width * sizeof(int));
        if (!map->data[i])
        {
            free_map(map);
            return (0);
        }
        // Use memset to initialize the allocated memory to 0
        memset(map->data[i], 0, map->width * sizeof(int));
        i++;
    }
    return (1);
}

static int validate_dimensions(const char *line, t_map *map)
{
    char **tokens;
    int   col;

    tokens = ft_split(line, ' ');
    if (!tokens)
        return (0);
    col = 0;
    while (tokens[col])
        col++;
    if (map->width == 0)
        map->width = col;
    else if (col != map->width)
    {
        free_2d_array(tokens);
        return (0);
    }
    free_2d_array(tokens);
    return (1);
}

static int count_dimensions(const char *filename, t_map *map)
{
    int     fd;
    char    *line;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    map->height = 0;
    map->width = 0;
    while ((line = get_next_line(fd)) != NULL)
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
    }
    close(fd);
    return (1);
}

static int parse_values(const char *filename, t_map *map)
{
    int     fd;
    char    *line;
    char    **tokens;
    int     row;
    int     col;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    row = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        tokens = ft_split(line, ' ');
        if (!tokens)
        {
            free(line);
            close(fd);
            return (0);
        }
        col = 0;
        while (tokens[col])
        {
            // Remove trailing newline if present
            char *trimmed = ft_strtrim(tokens[col], "\n");
            ft_printf_fd(STDERR, "Debug: Processing Row %d, Col %d, Token: '%s'\n", row, col, trimmed);
            map->data[row][col] = parse_strict_atoi(trimmed, tokens);
            ft_printf_fd(STDERR, "Debug: Stored map->data[%d][%d] = %d\n", row, col, map->data[row][col]);
            free(trimmed); // Free the trimmed token
            col++;
        }
        row++;
        free(line);
        free_2d_array(tokens);
    }
    close(fd);
    return (1);
}

int parse_map(const char *filename, t_map *map)
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