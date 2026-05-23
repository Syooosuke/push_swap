/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:11:10 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 20:23:45 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(int n)
{
	int	bits;
	int	max_rank;

	bits = 0;
	max_rank = n - 1;
	while (max_rank > 0)
	{
		max_rank >>= 1;
		bits++;
	}
	return (bits);
}

static void	radix_pass(t_stack *a, t_stack *b, t_bench *bench, int bit)
{
	int	size;
	int	i;

	size = a->size;
	i = 0;
	while (i < size)
	{
		if ((a->top->rank >> bit) & 1)
			op_ra(a, bench);
		else
			op_pb(a, b, bench);
		i++;
	}
	while (b->size > 0)
		op_pa(a, b, bench);
}

void	sort_complex(t_stack *a, t_stack *b, t_bench *bench)
{
	int	bits;
	int	i;

	assign_ranks(a);
	bits = get_max_bits(a->size);
	i = 0;
	while (i < bits)
	{
		radix_pass(a, b, bench, i);
		i++;
	}
}
