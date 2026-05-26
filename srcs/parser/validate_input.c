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

int	is_valid_int_str(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_in_int_range(char *s)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		num = num * 10 + (*s - '0');
		if ((sign == 1 && num > 2147483647)
			|| (sign == -1 && num > 2147483648))
			return (0);
		s++;
	}
	return (1);
}

int	has_deplicate(t_stack *a, int value)
{
	t_node	*current;

	current = a->top;
	while (current)
	{
		if (current->value == value)
			return (0);
		current = current->next;
	}
	return (1);
}

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
