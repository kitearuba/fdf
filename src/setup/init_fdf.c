/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:54:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

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
	mlx_hook(fdf->win, 2, 1L << 0, handle_key_press, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, handle_key_release, fdf);
	mlx_loop_hook(fdf->mlx, update_frame, fdf);
	return (fdf);
}
