/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:06:54 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 12:08:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   free_2d_array                                                            */
/*                                                                            */
/*   Frees a dynamically allocated 2D array of strings.                       */
/*   Iterates through each element of the array, freeing each string          */
/*   individually, before freeing the array itself. Ensures no memory leaks   */
/*   by setting freed pointers to NULL.                                       */
/*                                                                            */
/*   @param arr: A pointer to the 2D array to be freed.                       */
/*   @return: None.                                                           */
/*                                                                            */
/* ************************************************************************** */

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
