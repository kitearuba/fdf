/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/28 23:00:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                          Error Handling & Cleanup                          */
/* ************************************************************************** */

void	free_resources_on_error(char **str, const char *error_message)
{
	if (map->data)
		free_2d_array(map->data);
	/*if (map->height >= 0)
		close(map->infile);
	if (map->outfile >= 0)
		close(map->outfile);*/
        fatal_error(error_message);
}