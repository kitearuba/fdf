/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:29:05 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/31 01:07:17 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   fatal_error                                                              */
/*                                                                            */
/*   Prints an error message to STDERR and exits the program.                 */
/*   This function is used to terminate execution on critical errors.         */
/*                                                                            */
/* ************************************************************************** */

void	fatal_error(void)
{
	ft_printf_fd(STDERR, "Error\n");
	exit(EXIT_FAILURE);
}
