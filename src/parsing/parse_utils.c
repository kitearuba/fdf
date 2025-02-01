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
  int		col;

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
    while (tokens[col])
    {
      trimmed = ft_strtrim(tokens[col], "\n");
      map->data[*row][col] = parse_strict_atoi(trimmed, tokens);
      free(trimmed);
      col++;
    }
    free_2d_array(tokens);
    (*row)++;
    line = get_next_line(fd);
  }
  return (1);
}