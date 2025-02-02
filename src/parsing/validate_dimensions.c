/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 23:24:07 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 23:27:40 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	handle_invalid_line(const char *line)
{
	if (!line || !*line)
	{
		ft_printf_fd(STDERR, "Invalid input detected (empty string)\n");
		return (0);
	}
	return (1);
}

static int	is_valid_number(const char *str)
{
	if (!ft_isdigit(str[0]) && str[0] != '-')
	{
		ft_printf_fd(STDERR, "Error: Non-numeric value found: %s\n", str);
		return (0);
	}
	return (1);
}

int	validate_dimensions(const char *line, t_map *map)
{
	char	**tokens;
	int		col_count;

	if (!handle_invalid_line(line))
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		ft_printf_fd(STDERR, "Error: ft_split failed on line: %s\n", line);
		return (0);
	}
	col_count = 0;
	while (tokens[col_count])
	{
		if (!is_valid_number(tokens[col_count]))
		{
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
