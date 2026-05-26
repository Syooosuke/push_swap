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

static void	putnbr_fd(int n, int fd)
{
	char	c;

	if (n >= 10)
		putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static int	total_ops(t_bench *bench)
{
	return (bench->count_sa + bench->count_sb + bench->count_ss
		+ bench->count_pa + bench->count_pb + bench->count_ra
		+ bench->count_rb + bench->count_rr + bench->count_rra
		+ bench->count_rrb + bench->count_rrr);
}

static void	put_count(char *name, int count)
{
	write(STDERR_FILENO, name, 3);
	write(STDERR_FILENO, "=", 1);
	putnbr_fd(count, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	print_bench(t_bench *bench)
{
	if (!bench->enabled)
		return ;
	write(STDERR_FILENO, "total=", 6);
	putnbr_fd(total_ops(bench), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	put_count("sa ", bench->count_sa);
	put_count("sb ", bench->count_sb);
	put_count("ss ", bench->count_ss);
	put_count("pa ", bench->count_pa);
	put_count("pb ", bench->count_pb);
	put_count("ra ", bench->count_ra);
	put_count("rb ", bench->count_rb);
	put_count("rr ", bench->count_rr);
	put_count("rra", bench->count_rra);
	put_count("rrb", bench->count_rrb);
	put_count("rrr", bench->count_rrr);
}
