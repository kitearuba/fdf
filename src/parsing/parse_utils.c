/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:27:34 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	validate_dimensions(const char *line, t_map *map)
{
  char	**tokens;
  int		col_count;

  if (!line || !*line)
  {
    ft_printf_fd(STDERR, "Invalid input detected (empty string)\n");
    return (0);
  }
  tokens = ft_split(line, ' ');
  if (!tokens)
  {
    ft_printf_fd(STDERR, "Error: ft_split failed on line: %s\n", line);
    return (0);
  }
  col_count = 0;
  while (tokens[col_count])
  {
    if (!ft_isdigit(tokens[col_count][0]) && tokens[col_count][0] != '-')
    {
      ft_printf_fd(STDERR, "Error: Non-numeric value found: %s\n", tokens[col_count]);
      free_2d_array(tokens);
      return (0);
    }
    col_count++;
  }
  if (col_count > map->width)
    map->width = col_count;
  free_2d_array(tokens);
  return (1);
}

int	parse_rows(int fd, t_map *map, int *row)
{
  char	*line;
  char	**tokens;
  int		col;
  char	*trimmed;

  line = get_next_line(fd);
  while (line)
  {
    tokens = ft_split(line, ' ');
    free(line);
    if (!tokens)
      return (0);
    col = 0;
    while (tokens[col] && col < map->width)
    {
      trimmed = ft_strtrim(tokens[col], "\n");
      map->data[*row][col] = parse_strict_atoi(trimmed, tokens);
      free(trimmed);
      col++;
    }
    while (col < map->width)
      map->data[*row][col++] = 0;

    free_2d_array(tokens);
    (*row)++;
    line = get_next_line(fd);
  }
  return (1);
}
