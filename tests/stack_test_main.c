/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:35:00 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 16:35:00 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

static int	parse_values(int argc, char **argv, int *values)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		values[i - 1] = atoi(argv[i]);
		i++;
	}
	return (argc - 1);
}

static void	bench_init(t_bench *bench)
{
	bench->enabled = 1;
	bench->disorder = 0;
	bench->strategy_used = START_SIMPLE;
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

static int	push_values(t_stack *a, int *values, int size)
{
	t_node	*node;
	int		i;

	i = 0;
	while (i < size)
	{
		node = node_new(values[i]);
		if (!node)
			return (1);
		stack_push_bottom(a, node);
		i++;
	}
	return (0);
}

static int	is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

static int	count_nodes(t_stack *stack)
{
	t_node	*current;
	int		count;

	count = 0;
	current = stack->top;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	print_stack(char *name, t_stack *stack)
{
	t_node	*current;

	printf("%s(size=%d):", name, stack->size);
	current = stack->top;
	while (current)
	{
		printf(" %d", current->value);
		current = current->next;
	}
	printf("\n");
}

static int	expect_sorted_case(char *name, int *values, int size)
{
	t_stack	*a;
	t_stack	*b;
	t_bench	bench;
	int		failed;

	failed = 0;
	a = stack_init();
	b = stack_init();
	if (!a || !b || push_values(a, values, size))
	{
		stack_free(a);
		stack_free(b);
		printf("[NG] %s: failed to initialize stacks\n", name);
		return (1);
	}
	bench_init(&bench);
	printf("\n--- %s ---\n", name);
	print_stack("before A", a);
	fflush(stdout);
	sort_simple(a, b, &bench);
	print_stack("after  A", a);
	print_stack("after  B", b);
	if (!is_sorted(a))
		failed = 1;
	if (a->size != size || count_nodes(a) != size)
		failed = 1;
	if (b->size != 0 || count_nodes(b) != 0)
		failed = 1;
	if (failed)
		printf("[NG] %s\n", name);
	else
		printf("[OK] %s\n", name);
	printf("ops: sa=%d pa=%d pb=%d ra=%d rra=%d total=%d\n",
		bench.count_sa, bench.count_pa, bench.count_pb,
		bench.count_ra, bench.count_rra,
		bench.count_sa + bench.count_pa + bench.count_pb
		+ bench.count_ra + bench.count_rra);
	stack_free(a);
	stack_free(b);
	return (failed);
}

int	main(int argc, char **argv)
{
	int	failed;
	int	two_unsorted[2] = {2, 1};
	int	three_unsorted[3] = {2, 3, 1};
	int	three_reverse[3] = {3, 2, 1};
	int	five_mixed[5] = {4, 1, 5, 2, 3};
	int	five_reverse[5] = {5, 4, 3, 2, 1};
	int	*values;

	failed = 0;
	if (argc > 1)
	{
		values = malloc(sizeof(int) * (argc - 1));
		if (!values)
			return (1);
		failed = expect_sorted_case("argv random case", values,
				parse_values(argc, argv, values));
		free(values);
		return (failed != 0);
	}
	failed += expect_sorted_case("two unsorted", two_unsorted, 2);
	failed += expect_sorted_case("three unsorted", three_unsorted, 3);
	failed += expect_sorted_case("three reverse", three_reverse, 3);
	failed += expect_sorted_case("five mixed", five_mixed, 5);
	failed += expect_sorted_case("five reverse", five_reverse, 5);
	if (failed == 0)
		printf("\nAll simple_sort tests passed.\n");
	else
		printf("\n%d simple_sort test(s) failed.\n", failed);
	return (failed != 0);
}
