/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:25:24 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 20:30:20 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_stack *a, t_stack *b, t_bench *bench, double disorder)
{
	if (disorder < 0.2)
		sort_simple(a, b, bench);
	else if (0.2 <= disorder && disorder < 0.5)
		sort_medium(a, b, bench);
	else
		sort_complex(a, b, bench);
}
