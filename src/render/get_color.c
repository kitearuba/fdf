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

	if (max_z == min_z)  // Edge case where all values are the same
		return (0xFFFFFF);
	ratio = (float)(z - min_z) / (max_z - min_z);
	if (ratio < 0.0)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	red = (int)(255 * ratio);
	green = (int)(255 * (1 - ratio));
	blue = 255;
	return ((red << 16) | (green << 8) | blue);
}
