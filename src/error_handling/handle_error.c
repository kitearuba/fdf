/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:32:55 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/15 18:22:41 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   handle_error                                                             */
/*                                                                            */
/*   Handles errors by cleaning up resources and exiting the program.         */
/*   Frees both stacks (if they exist) and triggers a fatal error.            */
/*                                                                            */
/*   @param a: Pointer to stack A.                                            */
/*   @param b: Pointer to stack B.                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	handle_error(t_stack *a, t_stack *b)
{
	if (a)
		stack_free(&a);
	if (b)
		stack_free(&b);
	fatal_error();
}
