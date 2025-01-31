/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 21:54:02 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                          Error Handling & Cleanup                          */
/* ************************************************************************** */

void	free_on_error(t_fdf *fdf, const char *error_message)
{
	if (fdf)
	{
		if (fdf->map)
			free_map(fdf->map);
		if (fdf->win)
		{
			mlx_destroy_window(fdf->mlx, fdf->win);
			fdf->win = NULL;
		}
		if (fdf->mlx)
		{
			free(fdf->mlx);
			fdf->mlx = NULL;
		}
		free(fdf);
	}
	fatal_error(error_message);
}
