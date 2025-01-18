/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/15 20:54:10 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   stack_new                                                                */
/*                                                                            */
/*   Creates a new a node with the given value.                               */
/*                                                                            */
/* ************************************************************************** */
static t_stack	*stack_new(long value)
{
	t_stack	*new_node;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
	{
		stack_free(&new_node);
		fatal_error();
	}
	new_node->nbr = value;
	new_node->next = NULL;
	return (new_node);
}

/* ************************************************************************** */
/*                                                                            */
/*   add_to_stack                                                             */
/*                                                                            */
/*   Adds a new node with the given value to the a.                           */
/*   Creates a new node using `stack_new` and appends it to the end of the    */
/*   a. If the a is empty, the new node becomes the first node.               */
/*                                                                            */
/*   @param a: A pointer to the pointer of the a.                             */
/*   @param value: The value to add to the a.                                 */
/*                                                                            */
/* ************************************************************************** */
static void	add_to_stack(t_stack **a, t_stack *stack_new)
{
	if (!a)
		return ;
	if (!*a)
		*a = stack_new;
	else
		(get_last_node(*a))->next = stack_new;
}

/* ************************************************************************** */
/*                                                                            */
/*   has_duplicates                                                           */
/*                                                                            */
/*   Checks for duplicate values in the a.                                    */
/*   Iterates through each node in the a and compares its value               */
/*   with the values of subsequent nodes. If a duplicate is found,            */
/*   it immediately triggers an error using `handle_error`.                   */
/*                                                                            */
/*   @param a: The a to check for duplicates.                                 */
/*   @return: Always returns 0 if no duplicates are found.                    */
/*                                                                            */
/* ************************************************************************** */
static int	has_duplicates(t_stack *a)
{
	t_stack	*current_node;
	t_stack	*comparison_node;

	current_node = a;
	while (current_node)
	{
		comparison_node = current_node->next;
		while (comparison_node)
		{
			if (current_node->nbr == comparison_node->nbr)
				handle_error(a, NULL);
			comparison_node = comparison_node->next;
		}
		current_node = current_node->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   validate_two_args                                                        */
/*                                                                            */
/*   Validates and parses arguments when only one argument is provided.       */
/*   Splits the single argument string into individual numbers using          */
/*   `ft_split`, parses each number with `parse_strict_atoi`, and adds        */
/*   them to the a.                                                           */
/*                                                                            */
/*   @param argv: The array of command-line arguments.                        */
/*   @return: The constructed a with the parsed values.                       */
/*                                                                            */
/* ************************************************************************** */
static t_stack	*validate_two_args(char **argv)
{
	t_stack	*a;
	char	**split_args;
	int		index;
	int		parsed_value;

	a = NULL;
	split_args = ft_split(argv[1], ' ');
	if (!split_args || !*split_args)
	{
		if (split_args)
			free_2d_array(split_args);
		fatal_error();
	}
	index = 0;
	while (split_args[index])
	{
		parsed_value = parse_strict_atoi(split_args[index], &a, split_args);
		add_to_stack(&a, stack_new(parsed_value));
		index++;
	}
	free_2d_array(split_args);
	return (a);
}

/* ************************************************************************** */
/*                                                                            */
/*   validate_arguments                                                       */
/*                                                                            */
/*   Main validation function for command-line arguments.                     */
/*   Validates the input arguments and constructs the a. If only one          */
/*   argument is provided, it calls `validate_two_args`. Otherwise, it        */
/*   iterates through the arguments, parses them, and adds each value         */
/*   to the a using `add_to_stack`.                                           */
/*                                                                            */
/*   @param a: A pointer to the pointer of the a to populate.                 */
/*                                                                            */
/* ************************************************************************** */
t_stack	*validate_arguments(int argc, char **argv)
{
	t_stack	*a;
	int		index;
	int		parsed_value;

	a = NULL;
	index = 1;
	if (argc == 2)
		a = validate_two_args(argv);
	else
	{
		while (index < argc)
		{
			parsed_value = parse_strict_atoi(argv[index], &a, NULL);
			add_to_stack(&a, stack_new(parsed_value));
			index++;
		}
	}
	if (has_duplicates(a))
		handle_error(a, NULL);
	return (a);
}
