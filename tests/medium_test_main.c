/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_test_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:10:00 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 20:10:00 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <fcntl.h>
#include <stdio.h>

static void	bench_init(t_bench *bench)
{
	bench->enabled = 1;
	bench->disorder = 0;
	bench->strategy_used = START_MEDIUM;
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

static int	total_ops(t_bench *bench)
{
	return (bench->count_sa + bench->count_sb + bench->count_ss
		+ bench->count_pa + bench->count_pb + bench->count_ra
		+ bench->count_rb + bench->count_rr + bench->count_rra
		+ bench->count_rrb + bench->count_rrr);
}

static void	sort_quietly(t_stack *a, t_stack *b, t_bench *bench)
{
	int	saved_stdout;
	int	null_fd;

	fflush(stdout);
	saved_stdout = dup(STDOUT_FILENO);
	null_fd = open("/dev/null", O_WRONLY);
	if (saved_stdout == -1 || null_fd == -1)
	{
		sort_medium(a, b, bench);
		if (saved_stdout != -1)
			close(saved_stdout);
		if (null_fd != -1)
			close(null_fd);
		return ;
	}
	dup2(null_fd, STDOUT_FILENO);
	sort_medium(a, b, bench);
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(null_fd);
}

static int	expect_sorted_case(char *name, int *values, int size)
{
	t_stack	*a;
	t_stack	*b;
	t_bench	bench;
	int		failed;
	double	disorder;

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
	disorder = compute_disorder(a);
	sort_quietly(a, b, &bench);
	if (!is_sorted(a))
		failed = 1;
	if (a->size != size || count_nodes(a) != size)
		failed = 1;
	if (b->size != 0 || count_nodes(b) != 0)
		failed = 1;
	if (failed)
		printf("[NG] %s: size=%d disorder=%.4f steps=%d\n",
			name, size, disorder, total_ops(&bench));
	else
		printf("[OK] %s: size=%d disorder=%.4f steps=%d\n",
			name, size, disorder, total_ops(&bench));
	stack_free(a);
	stack_free(b);
	return (failed);
}

int	main(int argc, char **argv)
{
	int	failed;
	int	ten_mixed[10] = {8, 3, 10, 1, 6, 2, 9, 5, 7, 4};
	int	ten_reverse[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int	ten_negative[10] = {-3, 12, 0, -8, 5, 21, -1, 7, -13, 2};
	int	twenty_mixed[20] = {15, 3, 20, 1, 9, 12, 6, 18, 4, 10,
			2, 17, 8, 14, 5, 19, 11, 7, 16, 13};
	int	*values;

	failed = 0;
	if (argc > 1)
	{
		values = malloc(sizeof(int) * (argc - 1));
		if (!values)
			return (1);
		failed = expect_sorted_case("argv random medium case", values,
				parse_values(argc, argv, values));
		free(values);
		return (failed != 0);
	}
	failed += expect_sorted_case("ten mixed", ten_mixed, 10);
	failed += expect_sorted_case("ten reverse", ten_reverse, 10);
	failed += expect_sorted_case("ten negative", ten_negative, 10);
	failed += expect_sorted_case("twenty mixed", twenty_mixed, 20);
	if (failed == 0)
		printf("\nAll medium_sort tests passed.\n");
	else
		printf("\n%d medium_sort test(s) failed.\n", failed);
	return (failed != 0);
}
