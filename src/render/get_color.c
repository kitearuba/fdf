/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/30 23:45:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int get_color(int z, int min_z, int max_z)
{
  float ratio;
  int red, green, blue;

  if (max_z == min_z)
    return (0xFFFFFF); // Default white if flat map

  ratio = (float)(z - min_z) / (max_z - min_z); // Normalize z between 0 and 1

  red = (int)(255 * ratio);  // More red for higher altitude
  green = (int)(255 * (1 - ratio)); // Less green as altitude increases
  blue = 255; // Keep blue constant

  return ((red << 16) | (green << 8) | blue); // Combine RGB
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