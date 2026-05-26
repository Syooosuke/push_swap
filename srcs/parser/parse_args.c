/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:58:04 by atajima           #+#    #+#             */
/*   Updated: 2026/05/26 18:28:38 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_strat_flag(char *arg, t_strategy *strat)
{
	if (ft_strncmp(arg, "--simple", 9) == 0)
	{
		*strat = START_SIMPLE;
		return (1);
	}
	if (ft_strncmp(arg, "--medium", 9) == 0)
	{
		*strat = START_MEDIUM;
		return (1);
	}
	if (ft_strncmp(arg, "--complex", 9) == 0)
	{
		*strat = START_COMPLEX;
		return (1);
	}
	if (ft_strncmp(arg, "--adaptive", 9) == 0)
	{
		*strat = START_ADAPTIVE;
		return (1);
	}
	return (0);
}

int	is_flag(char *arg)
{
	return (arg[0] == '-' && arg[1] == '-');
}

void	parse_flag(int argc, char **argv, t_strategy *strat, t_bench *bench)
{
	int	i;

	*strat = START_ADAPTIVE;
	bench->enabled = 0;
	i = 1;
	while (i < argc)
	{
		if (parse_strat_flag(argv[i], strat) == 0)
			if (ft_strncmp(argv[i], "--bench", 8) == 0)
				bench->enabled = 1;
		i++;
	}
}

static void	parse_split_str(t_stack *a, char *arg)
{
	char	**split;
	int		i;

	if (ft_strchr(arg, ' '))
	{
		split = ft_split(arg, ' ');
		if (!split)
		{
			stack_free(a);
			error_exit();
		}
		i = 0;
		while (split[i])
		{
			validate_and_push(a, split[i]);
			i++;
		}
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
	}
	else
		validate_and_push(a, arg);
}
//splitとnumbersでちょっと役割被ってる部分ある
void	parse_numbers(int argc, char **argv, t_stack *a)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i]))
		{
			if (ft_strchr(argv[i], ' '))
				parse_split_str(a, argv[i]);
			else
				validate_and_push(a, argv[i]);
		}
		i++;
	}
}

int	parse_args(int argc, char **argv, t_stack *a, t_bench *bench)
{
	parse_flag(argc, argv, &bench->strategy_used, bench);
	parse_numbers(argc, argv, a);
	return (0);
}

// static void free_split(char **split)
// {
// 	int i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }
