/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void find_min_max_z(t_fdf *fdf)
{
  int i, j;

  fdf->min_z = fdf->map->data[0][0];
  fdf->max_z = fdf->map->data[0][0];

  for (i = 0; i < fdf->map->height; i++)
  {
    for (j = 0; j < fdf->map->width; j++)
    {
      if (fdf->map->data[i][j] < fdf->min_z)
        fdf->min_z = fdf->map->data[i][j];
      if (fdf->map->data[i][j] > fdf->max_z)
        fdf->max_z = fdf->map->data[i][j];
    }
  }
}

/*
void find_min_max_z(t_fdf *fdf)
{
  int x, y;

  fdf->min_z = fdf->map->data[0][0];
  fdf->max_z = fdf->map->data[0][0];

  y = 0;
  while (y < fdf->map->height)
  {
    x = 0;
    while (x < fdf->map->width)
    {
      if (fdf->map->data[y][x] < fdf->min_z)
        fdf->min_z = fdf->map->data[y][x];
      if (fdf->map->data[y][x] > fdf->max_z)
        fdf->max_z = fdf->map->data[y][x];
      x++;
    }
    y++;
  }
}
*/