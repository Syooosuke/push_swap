/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:30:40 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 19:18:12 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *lst)
{
	t_node	*node;

	if (lst->size < 2)
		return ;
	node = stack_pop_top(lst);
	stack_push_bottom(lst, node);
}

void	op_ra(t_stack *a, t_bench *bench)
{
	rotate(a);
	write(STDOUT_FILENO, "ra\n", 3);
	if (bench->enabled)
		bench->count_ra++;
}

void	op_rb(t_stack *b, t_bench *bench)
{
	rotate(b);
	write(STDOUT_FILENO, "rb\n", 3);
	if (bench->enabled)
		bench->count_rb++;
}

void	op_rr(t_stack *a, t_stack *b, t_bench *bench)
{
	rotate(a);
	rotate(b);
	write(STDOUT_FILENO, "rr\n", 3);
	if (bench->enabled)
		bench->count_rr++;
}
