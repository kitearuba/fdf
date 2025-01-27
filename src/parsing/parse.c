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

// Function to free the map data
void free_map(t_map *map)
{
  int i;

  i = 0;
  if (map->data)
  {
    while (i < map->height)
    {
      free(map->data[i]);
      i++;
    }
    free(map->data);
  }
}

// Function to parse the .fdf file
int parse_map(const char *filename, t_map *map)
{
  int fd;
  char *line;
  char **tokens;
  int row = 0;
  int col;
  int i;

  i = 0;
  fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    ft_printf_fd(STDERR, "Error: Could not open file %s\n", filename);
    return (0);
  }
  // First pass: Count the number of lines (height) and tokens (width)
  map->height = 0;
  map->width = 0;
  while ((line = get_next_line(fd)) != NULL)
  {
    tokens = ft_split(line, ' ');
    col = 0;
    while (tokens[col])
      col++;
    if (map->width == 0)
      map->width = col;
    else if (col != map->width)
    {
      ft_printf_fd(STDERR, "Error: Inconsistent row length at line %d\n", map->height + 1);
      free(line);
      free(tokens);
      close(fd);
      return (0);
    }
    map->height++;
    free(line);
    free_2d_array(tokens);
  }
  // Allocate memory for the map data
  map->data = (int **)malloc(map->height * sizeof(int *));
  if (!map->data)
  {
    ft_printf_fd(STDERR, "Error: Memory allocation failed\n");
    close(fd);
    return (0);
  }
  while (i < map->height)
  {
    map->data[i] = (int *)malloc(map->width * sizeof(int));
    if (!map->data[i])
    {
      ft_printf_fd(STDERR, "Error: Memory allocation failed\n");
      free_map(map);
      close(fd);
      return (0);
    }
    i++;
  }
  // Second pass: Read the file again and store the height values
  close(fd);
  fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    ft_printf_fd(STDERR, "Error: Could not open file %s\n", filename);
    free_map(map);
    return (0);
  }

  row = 0;
  while ((line = get_next_line(fd)) != NULL)
  {
    tokens = ft_split(line, ' ');
    col = 0;
    while (tokens[col])
    {
      map->data[row][col] = ft_atoi(tokens[col]);
      col++;
    }
    row++;
    free(line);
    free_2d_array(tokens);
  }

  close(fd);
  return (1);
}
