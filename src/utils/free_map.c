/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 23:19:34 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (map->data)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->data[i]);
			i++;
		}
		free(map->data);
		map->data = NULL;
	}
	map->height = 0;
	map->width = 0;
}
