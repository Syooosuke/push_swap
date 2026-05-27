/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:25:24 by atajima           #+#    #+#             */
/*   Updated: 2026/05/27 20:14:11 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_stack *a, t_stack *b, t_bench *bench, double disorder)
{
	double	practical_disorder;

	practical_disorder = compute_practical_disorder(a);
	if (a->size <= 5)
	{

		bench->calc_amount = START_SIMPLE;
		sort_simple(a, b, bench);
	}
	else if (a->size <= 100 || practical_disorder < 0.10
		|| (disorder < 0.20 && practical_disorder < 0.25))
	{
		bench->calc_amount = START_MEDIUM;
		sort_medium(a, b, bench);
	}
	else
	{
		bench->calc_amount = START_COMPLEX;
		sort_complex(a, b, bench);
	}
}
