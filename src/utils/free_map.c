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

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FREE MAP  :::                                 */
/*                                                                            */
/*   Function: free_map                                                       */
/*   Description: Frees all allocated memory for the map structure.           */
/*                                                                            */
/*   - Iterates through the 2D data array and frees each row.                 */
/*   - Frees the map's data array.                                            */
/*   - Resets the map dimensions to prevent accidental access.                */
/*                                                                            */
/*   @param map Pointer to the map structure to be freed.                     */
/*                                                                            */
/* ************************************************************************** */
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
