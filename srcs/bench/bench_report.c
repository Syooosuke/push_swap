/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_report.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:10:00 by atajima           #+#    #+#             */
/*   Updated: 2026/05/26 18:10:00 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static void	put_strategy(t_bench *bench)
{
	ft_putstr_fd("[bench] strategy:  ", STDERR_FILENO);
	if (bench->strategy_used == START_SIMPLE)
		ft_putstr_fd("Simple / O(n^2)", STDERR_FILENO);
	else if (bench->strategy_used == START_MEDIUM)
		ft_putstr_fd("Medium / O(n√n)", STDERR_FILENO);
	else if (bench->strategy_used == START_COMPLEX)
		ft_putstr_fd("Complex / O(n log n)", STDERR_FILENO);
	else
	{
		ft_putstr_fd("Adaptive / ", STDERR_FILENO);
		if (bench->calc_amount == START_SIMPLE)
			ft_putstr_fd("O(n^2)", STDERR_FILENO);
		else if (bench->calc_amount == START_MEDIUM)
			ft_putstr_fd("O(n√n)", STDERR_FILENO);
		else if (bench->calc_amount == START_COMPLEX)
			ft_putstr_fd("O(n log n)", STDERR_FILENO);
	}
	write(STDERR_FILENO, "\n", 1);
}

static void	put_count(char *name, int count)
{
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(":  ", STDERR_FILENO);
	ft_putnbr_fd(count, STDERR_FILENO);
}

static void	put_counts(t_bench *bench)
{
	ft_putstr_fd("[bench] ", STDERR_FILENO);
	put_count("sa", bench->count_sa);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("sb", bench->count_sb);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("ss", bench->count_ss);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("pa", bench->count_pa);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("pb", bench->count_pb);
	ft_putstr_fd("\n[bench] ", STDERR_FILENO);
	put_count("ra", bench->count_ra);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("rb", bench->count_rb);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("rr", bench->count_rr);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("rra", bench->count_rra);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("rrb", bench->count_rrb);
	ft_putstr_fd("  ", STDERR_FILENO);
	put_count("rrr", bench->count_rrr);
	write(STDERR_FILENO, "\n", 1);
}

static void	put_disorder(double disorder)
{
	int	scaled;

	scaled = (int)(disorder * 10000.0 + 0.5);
	ft_putstr_fd("[bench] disorder:  ", STDERR_FILENO);
	ft_putnbr_fd(scaled / 100, STDERR_FILENO);
	write(STDERR_FILENO, ".", 1);
	if (scaled % 100 < 10)
		write(STDERR_FILENO, "0", 1);
	ft_putnbr_fd(scaled % 100, STDERR_FILENO);
	write(STDERR_FILENO, "%\n", 2);
}

void	print_bench(t_bench *bench)
{
	int	total;

	total = bench->count_sa + bench->count_sb + bench->count_ss
		+ bench->count_pa + bench->count_pb + bench->count_ra
		+ bench->count_rb + bench->count_rr + bench->count_rra
		+ bench->count_rrb + bench->count_rrr;
	if (bench->enabled == 2)
	{
		ft_putnbr_fd(total, STDERR_FILENO);
		return ;
	}
	op_flush(bench);
	if (!bench->enabled)
		return ;
	put_disorder(bench->disorder);
	put_strategy(bench);
	ft_putstr_fd("[bench] total_ops:  ", STDERR_FILENO);
	ft_putnbr_fd(total, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	put_counts(bench);
}
