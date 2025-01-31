/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static t_point  projection_isometric(int x, int y, int z, t_fdf *fdf)
{
  t_point p;

  if (!fdf)
    fatal_error("Error: fdf structure is NULL\n");
  p.x = (x - y) * cos(0.523599) * fdf->zoom + fdf-> offset_x;
  p.y = (x + y) * sin(0.523599) * fdf->zoom - (z * fdf->zoom / 5) + fdf-> offset_y;
  p.z = z;
  if (p.x < 0 || p.y < 0)
  {
    ft_printf_fd(STDERR_FILENO, "Error: Computed point out of bounds (%d, %d)\n", p.x, p.y);
    exit(EXIT_FAILURE);
  }
  ft_printf("Debug: project_isometric(%d, %d, %d) -> Screen (%d, %d)\n",
        x, y, z, p.x, p.y);
  return (p);
}
/*
static void  draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
  int dx;
  int dy;
  int  sx;
  int  sy;
  int err;
  int e2;

  dx = abs(p2.x - p1.x);
  dy = abs(p2.y - p1.y);
  sx = (p1.x < p2.x) ? 1 : -1;
  sy = (p1.y < p2.y) ? 1 : -1;
  err = dx - dy;
  while (p1.x != p2.x || p1.y != p2.y)
  {
    mlx_pixel_put(fdf->mlx, fdf->win, p1.x, p1.y, color);
    e2 = err * 2;
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

static void draw_map(t_fdf *fdf)
{
  int x;
  int y;
  t_point p1;
  t_point p2;
  t_point p3;

  y = 0;
  while (y < fdf->map->height)
  {
    x = 0;
    while (x < fdf->map->width)
    {
      p1 = projection_isometric(x, y, fdf->map->data[y][x], fdf);
      ft_printf("Drawing Point (%d, %d) -> Screen (%d, %d)\n",
            x, y, p1.x, p1.y);
      if (x + 1 > fdf->map->width)
      {
        p2 = projection_isometric(x + 1, y, fdf->map->data[y][x + 1], fdf);
        ft_printf("Drawing Line from (%d, %d) to (%d, %d)\n",
              p1.x, p1.y, p2.x, p2.y);
        draw_line(fdf, p1, p2, 0xFFFFFF);
      }
      if (y + 1 > fdf->map->height)
      {
        p3 = projection_isometric(x, y + 1, fdf->map->data[y + 1][x], fdf);
        ft_printf("Drawing Line from (%d, %d) to (%d, %d)\n",
              p1.x, p1.y, p3.x, p3.y);
        draw_line(fdf, p1, p3, 0xFFFFFF);
      }
      x++;
    }
    y++;
  }
}
*/
void	draw_map(t_fdf *fdf)
{
  int	x;
  int	y;
  t_point point;

  if (!fdf || !fdf->map || !fdf->map->data)
  {
    ft_printf_fd(STDERR_FILENO, "Error: fdf or map data is NULL\n");
    exit(EXIT_FAILURE);
  }

  y = 0;
  while (y < fdf->map->height)
  {
    x = 0;
    while (x < fdf->map->width)
    {
      point = projection_isometric(x, y, fdf->map->data[y][x], fdf);
      if (point.x >= 0 && point.x < 1920 && point.y >= 0 && point.y < 1080)
        mlx_pixel_put(fdf->mlx, fdf->win, point.x, point.y, 0xFFFFFF);
      x++;
    }
    y++;
  }
}

int	handle_exit(t_fdf *fdf)
{
  ft_printf("Debug: Closing window...\n");
  mlx_destroy_window(fdf->mlx, fdf->win);
  free_fdf(fdf);
  return (0);
}

static int  handle_key(int key, t_fdf *fdf)
{
  if (key == 65307) // ESC
    		handle_exit(fdf);
//    mlx_destroy_window(fdf->mlx, fdf->win);
  return (0);
}

void  render_fdf(t_fdf *fdf)
{
  if (!fdf || !fdf->map)
  {
    ft_printf_fd(STDERR_FILENO, "Error: fdf or map is NULL\n");
    free_on_error(fdf, "Error: Invalid FDF structure");
  }
  draw_map(fdf);
  mlx_hook(fdf->win, 2, 1L << 0, handle_key, fdf); //key presss hook
  mlx_hook(fdf->win, 17, 1L << 11, handle_exit, fdf); //Close window with x button
  ft_printf("Debug: Entering mlx_loop...\n");
  mlx_loop(fdf->mlx); // Starts Minilibx event loop
  ft_printf("Debug: Exiting mlx_loop...\n");
}