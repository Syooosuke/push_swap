/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:24:00 by atajima           #+#    #+#             */
/*   Updated: 2026/05/26 17:24:00 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_bench(t_bench *bench)
{
	bench->enabled = 0;
	bench->disorder = 0.0;
	bench->strategy_used = START_ADAPTIVE;
	bench->count_sa = 0;
	bench->count_sb = 0;
	bench->count_ss = 0;
	bench->count_pa = 0;
	bench->count_pb = 0;
	bench->count_ra = 0;
	bench->count_rb = 0;
	bench->count_rr = 0;
	bench->count_rra = 0;
	bench->count_rrb = 0;
	bench->count_rrr = 0;
}

static int	is_sorted(t_stack *a)
{
	t_node	*current;

	current = a->top;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

static void	run_sort(t_stack *a, t_stack *b, t_strategy strat, t_bench *bench)
{
	bench->disorder = compute_disorder(a);
	bench->strategy_used = strat;
	if (strat == START_SIMPLE)
		sort_simple(a, b, bench);
	else if (strat == START_MEDIUM)
		sort_medium(a, b, bench);
	else if (strat == START_COMPLEX)
		sort_complex(a, b, bench);
	else
		sort_adaptive(a, b, bench, bench->disorder);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_bench		bench;

	if (argc < 2)
		return (0);
	init_bench(&bench);
	a = stack_init();
	b = stack_init();
	if (!a || !b)
	{
		stack_free(a);
		stack_free(b);
		error_exit();
	}
	parse_args(argc, argv, a, &bench);
	if (!is_sorted(a))
		run_sort(a, b, bench.strategy_used, &bench);
	print_bench(&bench);
	stack_free(a);
	stack_free(b);
	return (0);
}
