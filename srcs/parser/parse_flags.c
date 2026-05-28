/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:49:12 by atajima           #+#    #+#             */
/*   Updated: 2026/05/28 18:49:12 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_same_flag(char *arg, char *flag, size_t len)
{
	return (ft_strncmp(arg, flag, len + 1) == 0);
}

int	parse_strat_flag(char *arg, t_strategy *strat)
{
	if (is_same_flag(arg, "--simple", 8))
	{
		*strat = START_SIMPLE;
		return (1);
	}
	if (is_same_flag(arg, "--medium", 8))
	{
		*strat = START_MEDIUM;
		return (1);
	}
	if (is_same_flag(arg, "--complex", 9))
	{
		*strat = START_COMPLEX;
		return (1);
	}
	if (is_same_flag(arg, "--adaptive", 10))
	{
		*strat = START_ADAPTIVE;
		return (1);
	}
	return (0);
}

int	is_bench_flag(char *arg)
{
	return (is_same_flag(arg, "--bench", 7));
}

int	is_option(char *arg)
{
	return (arg[0] == '-' && arg[1] == '-');
}

int	is_flag(char *arg)
{
	return (is_bench_flag(arg)
		|| is_same_flag(arg, "--simple", 8)
		|| is_same_flag(arg, "--medium", 8)
		|| is_same_flag(arg, "--complex", 9)
		|| is_same_flag(arg, "--adaptive", 10));
}
