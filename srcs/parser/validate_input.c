/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:49:15 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 17:03:33 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	validate_and_push(t_stack *a, char *s)
{
	int		value;
	t_node	*node;

	if (!is_valid_int_str(s) || !is_in_int_range(s))
	{
		stack_free(a);
		error_exit();
	}
	value = ft_atoi(s);
	if (!has_deplicate(a, value))
	{
		stack_free(a);
		error_exit();
	}
	node = node_new(value);
	if (!node)
	{
		stack_free(a);
		error_exit();
	}
	stack_push_bottom(a, node);
}
