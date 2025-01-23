/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minilibx-linux/mlx.h"
#include <stdlib.h> // For exit() and abs()

# define ESC_KEY 65307 // Keycode for the ESC key on Linux

/* ************************************************************************** */
/* FUNCTION: draw_gradient
 * ------------------------
 * Draws a gradient background by setting pixel colors based on their position.
 *
 * PARAMETERS:
 * - mlx: Pointer to the MiniLibX connection.
 * - win: Pointer to the MiniLibX window.
 * - width: Width of the window.
 * - height: Height of the window.
 *
 * HOW IT WORKS:
 * - Loops through each pixel in the window.
 * - Computes a color based on the x (red) and y (green) coordinates.
 * - Uses mlx_pixel_put to draw the pixel with the calculated color.
 * ************************************************************************** */
void draw_gradient(void *mlx, void *win, int width, int height)
{
  int	x;
  int	y;
  int	color;

  y = 0;
  while (y < height)
  {
    x = 0;
    while (x < width)
    {
      color = (x * 255 / width) << 16 | (y * 255 / height) << 8;
      mlx_pixel_put(mlx, win, x, y, color);
      x++;
    }
    y++;
  }
}

/* ************************************************************************** */
/* FUNCTION: handle_key
 * ---------------------
 * Handles keyboard input and closes the program if ESC is pressed.
 *
 * PARAMETERS:
 * - key: The keycode of the pressed key.
 * - param: A void pointer (not used in this function).
 *
 * HOW IT WORKS:
 * - Checks if the key pressed is ESC (keycode 65307).
 * - If ESC is pressed, the program exits.
 * ************************************************************************** */
int handle_key(int key, void *param)
{
  if (key == ESC_KEY)
    exit(0);
  return 0;
}

/* ************************************************************************** */
/* FUNCTION: draw_line
 * --------------------
 * Draws a straight line between two points using Bresenham's algorithm.
 *
 * PARAMETERS:
 * - mlx: Pointer to the MiniLibX connection.
 * - win: Pointer to the MiniLibX window.
 * - x0, y0: Starting coordinates of the line.
 * - x1, y1: Ending coordinates of the line.
 * - color: Color of the line in hexadecimal (e.g., 0xFFFFFF for white).
 *
 * HOW IT WORKS:
 * - Computes the difference (dx, dy) and direction (sx, sy) between the points.
 * - Uses an error term (err) to determine when to increment the x or y coordinate.
 * - Loops until the end point is reached, drawing pixels along the way.
 * ************************************************************************** */
void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
  int	dx;
  int	dy;
  int	sx;
  int	sy;
  int	err;
  int	e2;

  dx = abs(x1 - x0);
  dy = abs(y1 - y0);
  sx = 1;
  if (x0 > x1)
    sx = -1;
  sy = 1;
  if (y0 > y1)
    sy = -1;
  err = dx - dy;
  while (1)
  {
    mlx_pixel_put(mlx, win, x0, y0, color);
    if (x0 == x1 && y0 ==y1)
      break;
    e2 = 2 * err;
    if (e2 > -dy)
    {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}

/* ************************************************************************** */
/* FUNCTION: fill_image
 * ---------------------
 * Fills an off-screen image with a gradient, manipulating its pixel buffer.
 *
 * PARAMETERS:
 * - data: Pointer to the pixel data of the image.
 * - width: Width of the image.
 * - height: Height of the image.
 * - bpp: Bits per pixel (used to calculate pixel size).
 * - size_line: Number of bytes in each row of the image.
 *
 * HOW IT WORKS:
 * - Loops through each pixel in the image buffer.
 * - Computes a color based on its position and assigns it directly to the buffer.
 * ************************************************************************** */
void    fill_image(char *data, int width, int height, int bpp, int size_line)
{
  int  x;
  int  y;
  int  color;
  int  offset;

  y = 0;
  while (y < height)
  {
    x = 0;
    while (x < width)
    {
      color = (x *255 / width) << 16 | (y * 255 / height) << 8; // Calculate color
      offset = y * size_line + x * (bpp / 8); // Calculate pixel offset
      *(int *)(data + offset) = color; // Assign color to the pixel
      x++;
    }
    y++;
  }
}



/* ************************************************************************** */
/* FUNCTION: main
 * ---------------
 * Entry point of the program. Sets up the MiniLibX environment and calls
 * functions to draw a gradient background, handle events, and draw a line.
 *
 * PARAMETERS:
 * - argc: Number of command-line arguments (not used here).
 * - argv: Array of command-line arguments (not used here).
 *
 * HOW IT WORKS:
 * - Initializes MiniLibX.
 * - Creates a window of specified width and height.
 * - Draws a gradient background.
 * - Hooks the ESC key to close the program.
 * - Draws a diagonal line across the window.
 * - Keeps the window open using mlx_loop.
 * ************************************************************************** */
int	main(int argc, char **argv)
{
	void *mlx;
	void *win;
	int width = 800;
	int height = 600;
   void *img;       // Image pointer
   char *data;      // Pointer to the image's pixel buffer
   int bpp;         // Bits per pixel
   int size_line;   // Bytes per row in the image
   int endian;      // Endianness of the image (not used directly here)

	// Initialize MiniLibX
	mlx = mlx_init();
	if (!mlx)
		return (1);

	// Create a new window
	win = mlx_new_window(mlx, width, height, "Image Manipulation");
	if (!win)
		return (1);

    img = mlx_new_image(mlx, width, height);
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    fill_image(data, width, height, bpp, size_line);
    mlx_put_image_to_window(mlx, win, img, 0 , 0);
    draw_line(mlx, win, 100, 100, 700, 500, 0xFFFFFF);

    mlx_hook(win, 2, 1L << 0, handle_key, NULL);
    /*
	mlx_pixel_put(mlx, win, 400, 300, 0xFFFFFF); // Draws a white pixel at (400, 300)
	*/
	// Keep the window open
	mlx_loop(mlx);
	/*if (argc < 2)
		return (1);*/
	return (0);
}
