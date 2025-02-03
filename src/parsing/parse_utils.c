/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 23:22:34 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	fill_map_values(char **split_value, t_map *map, int row, int col)
{
	if (split_value[0])
		map->data[row][col] = parse_strict_atoi(split_value[0], split_value);
	if (split_value[1])
		map->colors[row][col] =  ft_strtol(split_value[1], NULL, 16);
	else
		map->colors[row][col] = LIGHT_GREEN;
}

static int	process_tokens(char **tokens, t_map *map, int row)
{
	int		col;
	char	*trimmed;
	char	**split_value;

	col = 0;
	while (tokens[col] && col < map->width)
	{
		trimmed = ft_strtrim(tokens[col], "\n");
		split_value = ft_split(trimmed, ',');
		free(trimmed);
		fill_map_values(split_value, map, row, col);
		free_2d_array(split_value);
		col++;
	}
	while (col < map->width)
	{
		map->data[row][col] = 0;
		map->colors[row][col] = LIGHT_GREEN;
		col++;
	}
	return (1);
}

int	parse_rows(int fd, t_map *map, int *row)
{
	char	*line;
	char	**tokens;

	line = get_next_line(fd);
	while (line)
	{
		tokens = ft_split(line, ' ');
		free(line);
		if (!tokens)
			return (0);
		if (!process_tokens(tokens, map, *row))
		{
			free_2d_array(tokens);
			return (0);
		}
		free_2d_array(tokens);
		(*row)++;
		line = get_next_line(fd);
	}
	return (1);
}
