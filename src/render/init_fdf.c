/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/30 23:45:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	handle_exit(t_fdf *fdf)
{
    free_fdf(fdf);
    exit(0);
    return (0);
}

static void	set_window_size(t_fdf *fdf)
{
	fdf->win_width = 1080;
	fdf->win_height = 800;
}

static void	set_fixed_zoom(t_fdf *fdf, t_map *map)
{
	int	max_size;

	max_size = map->width > map->height ? map->width : map->height;
	fdf->zoom = 20;
	if (max_size > 50)
		fdf->zoom = 10;
	if (max_size > 100)
		fdf->zoom = 5;
}

static void	set_offset(t_fdf *fdf, t_map *map)
{
	int	center_x;
	int	center_y;

	// Correcting for isometric projection
	center_x = ((map->width - 1) - (map->height - 1)) * fdf->zoom / 2;
	center_y = ((map->width - 1) + (map->height - 1)) * fdf->zoom / 4;

	fdf->offset_x = fdf->win_width / 2 - center_x;
	fdf->offset_y = fdf->win_height / 2 - center_y;
}

static void	init_mlx_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		free_on_error(fdf, "Error: Failed to initialize MiniLibX");
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, "FDF");
	if (!fdf->win)
		free_on_error(fdf, "Error: Failed to create window");
}

static void	init_image_buffer(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
	if (!fdf->img.img)
		free_on_error(fdf, "Error: Failed to create image");
	fdf->img.addr = mlx_get_data_addr(fdf->img.img,
			&fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		fatal_error("Error: Memory allocation failed for FDF");
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->map = map;
	set_window_size(fdf);
	set_fixed_zoom(fdf, map);
	set_offset(fdf, map);
	init_mlx_window(fdf);
	init_image_buffer(fdf);
	mlx_hook(fdf->win, 17, 0, handle_exit, fdf);
	//mlx_key_hook(fdf->win, handle_key, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, handle_key_press, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, handle_key_release, fdf);
	mlx_loop_hook(fdf->mlx, update_frame, fdf); // Continuously check key states
	return (fdf);
}
