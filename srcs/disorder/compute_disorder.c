/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:45:20 by atajima           #+#    #+#             */
/*   Updated: 2026/05/27 17:16:39 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_inversion(t_node *node)
{
	t_node	*cmp;
	int		count;

	count = 0;
	cmp = node->next;
	while (cmp)
	{
		if (node->value > cmp->value)
			count++;
		cmp = cmp->next;
	}
	return (count);
}

double	compute_disorder(t_stack *a)
{
	t_node	*current;
	int		mistakes;
	int		total_pairs;

	if (a->size <= 1)
		return (0.0);
	mistakes = 0;
	total_pairs = a->size * (a->size - 1) / 2;
	current = a->top;
	while (current)
	{
		mistakes += count_inversion(current);
		current = current->next;
	}
	return ((double)mistakes / (double)total_pairs);
}
