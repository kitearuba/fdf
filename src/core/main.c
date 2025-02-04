/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 21:52:49 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                            :::  FDF Project  :::                           */
/*                                                                            */
/*   File: main.c                                                            */
/*   Description: Entry point of the FDF project.                            */
/*                                                                            */
/*   - Validates command-line arguments.                                     */
/*   - Parses the map from the provided file.                                */
/*   - Initializes the FDF structure.                                        */
/*   - Renders the map using MiniLibX.                                       */
/*   - Starts the MiniLibX event loop.                                       */
/*   - Frees allocated memory before exiting.                                */
/*                                                                            */
/*   @param argc Number of command-line arguments.                           */
/*   @param argv Array of command-line arguments.                            */
/*   @return int Program exit status.                                        */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_map	map;
	t_fdf	*fdf;

	if (argc != 2)
		fatal_error("Usage: ./fdf <filename>");
	if (!parse_map(argv[1], &map))
		fatal_error("Error: Failed to parse map");
	fdf = init_fdf(&map);
	if (!fdf)
	{
		free_map(&map);
		fatal_error("Error: Failed to initialize FDF");
	}
	render_fdf(fdf);
	mlx_loop(fdf->mlx);
	free_map(&map);
	free_fdf(fdf);
	return (0);
}
