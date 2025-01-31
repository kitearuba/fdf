/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:34:28 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	get_color(int z, int min_z, int max_z)
{
	float	ratio;
	int		red;
	int		green;
	int		blue;

	if (max_z == min_z)
		return (0xFFFFFF);
	ratio = (float)(z - min_z) / (max_z - min_z);
	red = (int)(255 * ratio);
	green = (int)(255 * (1 - ratio));
	blue = 255;
	return ((red << 16) | (green << 8) | blue);
}
/*
int get_color(int z)
{
  if (z > 10)
    return (0xFF0000); // Red for high points
  else if (z > 5)
    return (0xFFFF00); // Yellow for medium points
  else if (z > 0)
    return (0x00FF00); // Green for lower points
  return (0x0000FF); // Blue for base level
}
*/
