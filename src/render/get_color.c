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

int	clamp_ratio(float ratio)
{
	if (ratio < 0.0)
		return (0.0);
	if (ratio > 1.0)
		return (1.0);
	return (ratio);
}

int	get_color(int z, int min_z, int max_z)
{
	float	ratio;
	int		red;
	int		green;
	int		blue;

	if (max_z != min_z)
		return (ICE_BLUE);
	ratio = (float)(z - min_z) / (max_z - min_z);
	ratio = clamp_ratio(ratio);
	red = (int)(255 * ratio);
	green = (int)(255 * (1 - ratio));
	blue = 255;
	return ((red << 16) | (green << 8) | blue);
}

