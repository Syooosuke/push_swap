/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_practical_disorder.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:00:00 by atajima           #+#    #+#             */
/*   Updated: 2026/05/27 17:00:00 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	fill_values(t_stack *a, int *values)
{
	t_node	*current;
	int		i;

	current = a->top;
	i = 0;
	while (current)
	{
		values[i] = current->value;
		current = current->next;
		i++;
	}
	return (i);
}

static int	compute_lis_len(int *values, int *lis, int size)
{
	int	i;
	int	j;
	int	max_len;

	i = 0;
	max_len = 0;
	while (i < size)
	{
		lis[i] = 1;
		j = 0;
		while (j < i)
		{
			if (values[j] < values[i] && lis[j] + 1 > lis[i])
				lis[i] = lis[j] + 1;
			j++;
		}
		if (lis[i] > max_len)
			max_len = lis[i];
		i++;
	}
	return (max_len);
}

double	compute_practical_disorder(t_stack *a)
{
	int	*values;
	int	*lis;
	int	lis_len;

	if (!a || a->size <= 1)
		return (0.0);
	values = malloc(sizeof(int) * a->size);
	lis = malloc(sizeof(int) * a->size);
	if (!values || !lis)
	{
		free(values);
		free(lis);
		return (1.0);
	}
	fill_values(a, values);
	lis_len = compute_lis_len(values, lis, a->size);
	free(values);
	free(lis);
	return (1.0 - ((double)lis_len / (double)a->size));
}
