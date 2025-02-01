/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:54:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	set_window_size(t_fdf *fdf)
{
  fdf->win_width = 1920;
  fdf->win_height = 1080;
}

void	set_fixed_zoom(t_fdf *fdf, t_map *map)
{
  int	max_size;

  if (map->width > map->height)
    max_size = map->width;
  else
    max_size = map->height;
  fdf->zoom = 20;
  if (max_size > 50)
    fdf->zoom = 10;
  if (max_size > 100)
    fdf->zoom = 5;
}

void	set_offset(t_fdf *fdf, t_map *map)
{
  int	center_x;
  int	center_y;

  center_x = ((map->width - 1) - (map->height - 1)) * fdf->zoom / 2;
  center_y = ((map->width - 1) + (map->height - 1)) * fdf->zoom / 4;
  fdf->offset_x = fdf->win_width / 2 - center_x;
  fdf->offset_y = fdf->win_height / 2 - center_y;
}
