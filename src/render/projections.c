/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 04:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/01 04:49:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	apply_rotation_x(t_fdf *fdf, t_rotation *rot, int y, int z)
{
  rot->rad_x = fdf->rotation_x * (M_PI / 180);
  rot->tmp_y = y * cos(rot->rad_x) - z * sin(rot->rad_x);
  rot->tmp_z = y * sin(rot->rad_x) + z * cos(rot->rad_x);
}

static void	apply_rotation_y(t_fdf *fdf, t_rotation *rot, int x)
{
  rot->rad_y = fdf->rotation_y * (M_PI / 180);
  rot->tmp_x = x * cos(rot->rad_y) + rot->tmp_z * sin(rot->rad_y);
}

t_point project_parallel(t_fdf *fdf, int x, int y, int z)
{
    t_point p;

    p.x = (x * fdf->zoom) + fdf->offset_x;
    p.y = (y * fdf->zoom) - (z * fdf->zoom / 10) + fdf->offset_y;
    p.z = z;
    p.color = get_color(z, fdf->min_z, fdf->max_z);

    return p;
}

t_point	project_isometric(t_fdf *fdf, int x, int y, int z)
{
  t_point		p;
  t_rotation	rot;

  apply_rotation_x(fdf, &rot, y, z);
  apply_rotation_y(fdf, &rot, x);
  z = -x * sin(rot.rad_y) + rot.tmp_z * cos(rot.rad_y);
  y = rot.tmp_y;
  p.x = (rot.tmp_x - y) * cos(0.523599) * fdf->zoom + fdf->offset_x;
  p.y = (rot.tmp_x + y) * sin(0.523599) * fdf->zoom - (z * fdf->zoom / 10)
          + fdf->offset_y;
  return (p);
}

t_point project_point(t_fdf *fdf, int x, int y, int z)
{
  t_point p;

  if (fdf->projections == 0) // Isometric projection
  {
    float rad_x = fdf->rotation_x * (M_PI / 180);
    float rad_y = fdf->rotation_y * (M_PI / 180);
    float tmp_x, tmp_y, tmp_z;
    tmp_y = y * cos(rad_x) - z * sin(rad_x);
    tmp_z = y * sin(rad_x) + z * cos(rad_x);
    tmp_x = x * cos(rad_y) + tmp_z * sin(rad_y);
    z = -x * sin(rad_y) + tmp_z * cos(rad_y);
    y = tmp_y;
    p.x = (tmp_x - y) * cos(0.523599) * fdf->zoom + fdf->offset_x;
    p.y = (tmp_x + y) * sin(0.523599) * fdf->zoom - (z * fdf->zoom / 10) + fdf->offset_y;
  }
  else
  {
    p.x = (x * fdf->zoom) + fdf->offset_x;
    p.y = (y * fdf->zoom) - (z * fdf->zoom / 10) + fdf->offset_y;
  }
  p.z = z;
  p.color = get_color(z, fdf->min_z, fdf->max_z);
  return (p);
}
