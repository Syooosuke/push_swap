/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:01:47 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 19:30:07 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_pos(t_stack *a)
{
	t_node	*current;
	int		min_val;
	int		min_pos;
	int		pos;

	current = a->top;
	min_val = current->value;
	min_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->value < min_val)
		{
			min_val = current->value;
			min_pos = pos;
		}
		pos++;
		current = current->next;
	}
	return (min_pos);
}

static void	bring_min_to_top(t_stack *a, t_bench *bench)
{
	int	pos;
	int	half;

	pos = find_min_pos(a);
	half = a->size / 2;
	if (pos <= half)
	{
		while (pos > 0)
		{
			op_ra(a, bench);
			pos--;
		}
	}
	else
	{
		pos = a->size - pos;
		while (pos > 0)
		{
			op_rra(a, bench);
			pos--;
		}
	}
}

static void	sort_two(t_stack *a, t_bench *bench)
{
	if (a->top->value > a->top->next->value)
		op_sa(a, bench);
}

static void	sort_three(t_stack *a, t_bench *bench)
{
	int	top;
	int	mid;

	top = a->top->value;
	mid = a->top->next->value;
	if (top > mid && top > a->bottom->value && mid > a->bottom->value)
	{
		op_sa(a, bench);
		op_rra(a, bench);
	}
	else if (top > mid && top > a->bottom->value)
		op_ra(a, bench);
	else if (top < mid && mid > a->bottom->value && top < a->bottom->value)
	{
		op_rra(a, bench);
		if (a->top->value > a->top->next->value)
			op_sa(a, bench);
	}
	else if (top > mid && top < a->bottom->value)
		op_sa(a, bench);
	else if (top < mid && top > a->bottom->value)
		op_rra(a, bench);
}

void	sort_simple(t_stack *a, t_stack *b, t_bench *bench)
{
	while (a->size > 3)
	{
		bring_min_to_top(a, bench);
		op_pb(a, b, bench);
	}
	if (a->size == 2)
		sort_two(a, bench);
	else if (a->size == 3)
		sort_three(a, bench);
	while (b->size > 0)
		op_pa(a, b, bench);
}
