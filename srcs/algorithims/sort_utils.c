/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:13:02 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 20:13:41 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_ranks(t_stack *a)
{
	t_node	*current;
	t_node	*cmp;
	int		rank;

	current = a->top;
	while (current)
	{
		rank = 0;
		cmp = a->top;
		while (cmp)
		{
			if (cmp->value < current->value)
				rank++;
			cmp = cmp->next;
		}
		current->rank = rank;
		current = current->next;
	}
}
