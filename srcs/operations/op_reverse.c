/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:35:48 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 19:18:03 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_stack *lst)
{
	t_node	*node;

	if (lst->size < 2)
		return ;
	node = lst->bottom;
	lst->bottom = node->prev;
	lst->bottom->next = NULL;
	node->prev = NULL;
	lst->size--;
	stack_push_top(lst, node);
}

void	op_rra(t_stack *a, t_bench *bench)
{
	reverse_rotate(a);
	write(STDOUT_FILENO, "rra\n", 4);
	if (bench->enabled)
		bench->count_rra++;
}

void	op_rrb(t_stack *b, t_bench *bench)
{
	reverse_rotate(b);
	write(STDOUT_FILENO, "rrb\n", 4);
	if (bench->enabled)
		bench->count_rrb++;
}

void	op_rrr(t_stack *a, t_stack *b, t_bench *bench)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(STDOUT_FILENO, "rrr\n", 4);
	if (bench->enabled)
		bench->count_rrr++;
}
