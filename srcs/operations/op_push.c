/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:16:34 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 19:17:57 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_pa(t_stack *a, t_stack *b, t_bench *bench)
{
	t_node	*node;

	if (b->size == 0)
		return ;
	node = stack_pop_top(b);
	stack_push_top(a, node);
	write(STDOUT_FILENO, "pa\n", 3);
	if (bench->enabled)
		bench->count_pa++;
}

void	op_pb(t_stack *a, t_stack *b, t_bench *bench)
{
	t_node	*node;

	if (a->size == 0)
		return ;
	node = stack_pop_top(a);
	stack_push_top(b, node);
	write(STDOUT_FILENO, "pb\n", 3);
	if (bench->enabled)
		bench->count_pb++;
}
