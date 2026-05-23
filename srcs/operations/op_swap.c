/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:07:08 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 18:16:24 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_top(t_stack *lst)
{
	int	tmp_value;
	int	tmp_rank;

	if (lst->size < 2)
		return ;
	tmp_value = lst->top->value;
	tmp_rank = lst->top->rank;
	lst->top->value = lst->top->next->value;
	lst->top->rank = lst->top->next->rank;
	lst->top->next->value = tmp_value;
	lst->top->next->rank = tmp_rank;
}

void	op_sa(t_stack *a, t_bench *bench)
{
	swap_top(a);
	write(STDOUT_FILENO, "sa\n", 3);
	if (bench->enabled)
		bench->count_sa++;
}

void	op_sb(t_stack *b, t_bench *bench)
{
	swap_top(b);
	write(STDOUT_FILENO, "sb\n", 3);
	if (bench->enabled)
		bench->count_sb++;
}

void	op_ss(t_stack *a, t_stack *b, t_bench *bench)
{
	swap_top(a);
	swap_top(b);
	write(STDOUT_FILENO, "ss\n", 3);
	if (bench->enabled)
		bench->count_ss++;
}
