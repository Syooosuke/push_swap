/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 19:49:39 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 20:13:12 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_to_b(t_stack *a, t_stack *b, t_bench *bench)
{
	int	chunk_size;
	int	pushed;
	int	size;

	chunk_size = 1;
	while (chunk_size * chunk_size < a->size)
		chunk_size++;
	pushed = 0;
	while (a->size > 0)
	{
		size = a->size;
		while (size > 0)
		{
			if (a->top->rank < pushed + chunk_size)
				op_pb(a, b, bench);
			else
				op_ra(a, bench);
			size--;
		}
		pushed += chunk_size;
	}
}

static int	find_max_pos(t_stack *b)
{
	t_node	*current;
	int		max_rank;
	int		max_pos;
	int		pos;

	current = b->top;
	max_rank = current->rank;
	max_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->rank > max_rank)
		{
			max_rank = current->rank;
			max_pos = pos;
		}
		pos++;
		current = current->next;
	}
	return (max_pos);
}

static void	pull_to_a(t_stack *a, t_stack *b, t_bench *bench)
{
	int	pos;

	while (b->size > 0)
	{
		pos = find_max_pos(b);
		if (pos <= b->size / 2)
		{
			while (pos > 0)
			{
				op_rb(b, bench);
				pos--;
			}
		}
		else
		{
			pos = b->size - pos;
			while (pos > 0)
			{
				op_rrb(b, bench);
				pos--;
			}
		}
		op_pa(a, b, bench);
	}
}

void	sort_medium(t_stack *a, t_stack *b, t_bench *bench)
{
	assign_ranks(a);
	push_to_b(a, b, bench);
	pull_to_a(a, b, bench);
}
