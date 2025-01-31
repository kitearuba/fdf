/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:50:12 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/30 23:50:12 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void  put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
  char  *dst;

  if (x >= 0 && x < fdf->win_width && y >= 0 && y < fdf->win_height)
  {
    dst = fdf->img.addr + (y * fdf->img.line_length + x * (fdf->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
  }
}

static t_point project_isometric(t_fdf *fdf, int x, int y, int z)
{
  t_point p;
  float   rad_x, rad_y, tmp_x, tmp_y, tmp_z;

  rad_x = fdf->rotation_x * (M_PI / 180);
  rad_y = fdf->rotation_y * (M_PI / 180);

  tmp_y = y * cos(rad_x) - z * sin(rad_x);
  tmp_z = y * sin(rad_x) + z * cos(rad_x);
  tmp_x = x * cos(rad_y) + tmp_z * sin(rad_y);
  z = -x * sin(rad_y) + tmp_z * cos(rad_y);
  y = tmp_y;

  p.x = (tmp_x - y) * cos(0.523599) * fdf->zoom + fdf->offset_x;
  p.y = (tmp_x + y) * sin(0.523599) * fdf->zoom - (z * fdf->zoom / 10) + fdf->offset_y;

  // Assign color based on z value
 // p.color = get_color(z, fdf->min_z, fdf->max_z);

  return (p);
}

/*
static t_point project_isometric(t_fdf *fdf, int x, int y, int z)
{
  t_point p;
  float   rad_x;
  float   rad_y;
  float   tmp_x;
  float   tmp_y;
  float   tmp_z;

  // Convert angles to radians
  rad_x = fdf->rotation_x * (M_PI / 180);
  rad_y = fdf->rotation_y * (M_PI / 180);

  // Apply rotation around X-axis
  tmp_y = y * cos(rad_x) - z * sin(rad_x);
  tmp_z = y * sin(rad_x) + z * cos(rad_x);

  // Apply rotation around Y-axis
  tmp_x = x * cos(rad_y) + tmp_z * sin(rad_y);
  z = -x * sin(rad_y) + tmp_z * cos(rad_y);
  y = tmp_y;

  // Apply isometric projection with adjusted Z-scaling
  p.x = (tmp_x - y) * cos(0.523599) * fdf->zoom + fdf->offset_x;
  p.y = (tmp_x + y) * sin(0.523599) * fdf->zoom - (z * fdf->zoom / 10) + fdf->offset_y;

  return (p);
}
*/
static void draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
  int dx;
  int dy;
  int sx;
  int sy;
  int err;
  int e2;
  int color1;
  int color2;

  dx = abs(p2.x - p1.x);
  dy = abs(p2.y - p1.y);
  sx = (p1.x < p2.x) ? 1 : -1;
  sy = (p1.y < p2.y) ? 1 : -1;
  err = dx - dy;
  color1 = get_color(p1.z, fdf->min_z, fdf->max_z);
  color2 = get_color(p2.z, fdf->min_z, fdf->max_z);
  while (p1.x != p2.x || p1.y != p2.y)
  {
    put_pixel_to_image(fdf, p1.x, p1.y, color1);
    put_pixel_to_image(fdf, p2.x, p2.y, color2);
    e2 = 2 * err;
    if (e2 > -dy)
    {
      err -= dy;
      p1.x += sx;
    }
    if (e2 < dx)
    {
      err += dx;
      p1.y += sy;
    }
  }
}

static void draw_thick_line(t_fdf *fdf, t_point p1, t_point p2, int thickness)
{
  int offset;
  t_point new_p1;
  t_point new_p2;

  for (offset = -thickness / 2; offset <= thickness / 2; offset++)
  {
    new_p1 = p1;
    new_p2 = p2;

    // Adjust x and y for thickness effect
    if (abs(p2.x - p1.x) > abs(p2.y - p1.y))
    {
      new_p1.y += offset;
      new_p2.y += offset;
    }
    else
    {
      new_p1.x += offset;
      new_p2.x += offset;
    }

    draw_line(fdf, new_p1, new_p2); // Call the original draw_line function
  }
}

static void render_map(t_fdf *fdf)
{
  int x;
  int y;
  t_point p1;
  t_point p2;

  y = 0;
  while (y < fdf->map->height)
  {
    x = 0;
    while (x < fdf->map->width)
    {
      p1 = project_isometric(fdf, x, y, fdf->map->data[y][x]);
      if (x + 1 < fdf->map->width)
      {
        p2 = project_isometric(fdf, x + 1, y, fdf->map->data[y][x + 1]);
        //draw_line(fdf, p1, p2);
        draw_thick_line(fdf, p1, p2, 8); // Adjust thickness as needed

      }
      if (y + 1 < fdf->map->height)
      {
        p2 = project_isometric(fdf, x, y + 1, fdf->map->data[y + 1][x]);
        //draw_line(fdf, p1, p2);
        draw_thick_line(fdf, p1, p2, 3); // Adjust thickness as needed
      }
      x++;
    }
    y++;
  }
}

void render_fdf(t_fdf *fdf)
{
  ft_memset(fdf->img.addr, 0, fdf->win_height * fdf->img.line_length);
  render_map(fdf);
  mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
  mlx_loop(fdf->mlx);
}
