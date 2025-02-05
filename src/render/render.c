/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:50:12 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/05 22:00:12 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  DRAW HORIZONTAL LINE  :::                     */
/*                                                                            */
/*   Function: draw_horizontal_line                                           */
/*   Description: Draws a horizontal line connecting two adjacent points.     */
/*                                                                            */
/*   - Retrieves the Z values and assigns colors for both points.             */
/*   - Applies either isometric or parallel projection based on settings.     */
/*   - Calls draw_thick_line to render the final line.                        */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering data.       */
/*   @param x The x-coordinate of the starting point.                         */
/*   @param y The y-coordinate of the starting point.                         */
/*                                                                            */
/* ************************************************************************** */
static void	draw_horizontal_line(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1.x = x;
	p1.y = y;
	p1.z = fdf->map->data[y][x];
	p1.color = get_color(fdf, p1.z);
	p2.x = x + 1;
	p2.y = y;
	p2.z = fdf->map->data[y][x + 1];
	p2.color = get_color(fdf, p2.z);
	if (fdf->projections == 0)
	{
		p1 = apply_isometric(fdf, p1);
		p2 = apply_isometric(fdf, p2);
	}
	else
	{
		p1 = apply_parallel(fdf, p1.x, p1.y, p1.z);
		p2 = apply_parallel(fdf, p2.x + 1, p2.y, p2.z);
	}
	draw_thick_line(fdf, p1, p2);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  DRAW VERTICAL LINE  :::                       */
/*                                                                            */
/*   Function: draw_vertical_line                                             */
/*   Description: Draws a vertical line connecting two adjacent points.       */
/*                                                                            */
/*   - Retrieves the Z values and assigns colors for both points.             */
/*   - Applies either isometric or parallel projection based on settings.     */
/*   - Calls draw_thick_line to render the final line.                        */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering data.       */
/*   @param x The x-coordinate of the starting point.                         */
/*   @param y The y-coordinate of the starting point.                         */
/*                                                                            */
/* ************************************************************************** */
static void	draw_vertical_line(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1.x = x;
	p1.y = y;
	p1.z = fdf->map->data[y][x];
	p1.color = get_color(fdf, p1.z);
	p2.x = x;
	p2.y = y + 1;
	p2.z = fdf->map->data[y + 1][x];
	p2.color = get_color(fdf, p2.z);
	if (fdf->projections == 0)
	{
		p1 = apply_isometric(fdf, p1);
		p2 = apply_isometric(fdf, p2);
	}
	else
	{
		p1 = apply_parallel(fdf, p1.x, p1.y, p1.z);
		p2 = apply_parallel(fdf, p2.x, p2.y, p2.z);
	}
	draw_thick_line(fdf, p1, p2);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  RENDER MAP  :::                               */
/*                                                                            */
/*   Function: render_map                                                     */
/*   Description: Iterates through the map and draws the wireframe grid.      */
/*                                                                            */
/*   - Loops through all points in the map.                                   */
/*   - Calls draw_horizontal_line and draw_vertical_line where applicable.    */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering data.       */
/*                                                                            */
/* ************************************************************************** */
static void	render_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x + 1 < fdf->map->width)
				draw_horizontal_line(fdf, x, y);
			if (y + 1 < fdf->map->height)
				draw_vertical_line(fdf, x, y);
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  RENDER FDF  :::                               */
/*                                                                            */
/*   Function: render_fdf                                                     */
/*   Description: Clears the screen and renders the entire 3D model.         */
/*                                                                            */
/*   - Clears the image buffer before rendering.                              */
/*   - Calls find_min_max_z to determine height range for coloring.           */
/*   - Calls render_map to draw the entire structure.                         */
/*   - Places the final image onto the window using MiniLibX.                 */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering data.       */
/*                                                                            */
/* ************************************************************************** */
void	render_fdf(t_fdf *fdf)
{
	ft_memset(fdf->img.addr, 0, fdf->win_height * fdf->img.line_length);
	find_min_max_z(fdf);
	render_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
