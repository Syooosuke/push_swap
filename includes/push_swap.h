/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:57:33 by syokota           #+#    #+#             */
/*   Updated: 2026/05/27 20:09:57 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				rank;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef enum e_strategy
{
	START_SIMPLE,
	START_MEDIUM,
	START_COMPLEX,
	START_ADAPTIVE
}					t_strategy;

typedef struct s_stack
{
	t_node			*top;
	t_node			*bottom;
	int				size;
}					t_stack;

typedef struct s_bench
{
	int				enabled;
	double			disorder;
	t_strategy		strategy_used;
	t_strategy		calc_amount;
	int				count_sa;
	int				count_sb;
	int				count_ss;
	int				count_pa;
	int				count_pb;
	int				count_ra;
	int				count_rb;
	int				count_rr;
	int				count_rra;
	int				count_rrb;
	int				count_rrr;
}					t_bench;

int					parse_args(int argc, char **argv, t_stack *a,
						t_bench *bench);
void				error_exit(void);
int					ft_atoi(const char *nptr);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(char const *s, char c);
t_node				*node_new(int value);
t_stack				*stack_init(void);
void				stack_push_bottom(t_stack *lst, t_node *node);
void				stack_push_top(t_stack *lst, t_node *node);
t_node				*stack_pop_top(t_stack *lst);
void				stack_free(t_stack *s);
int					is_valid_int_str(char *s);
int					is_in_int_range(char *s);
int					has_deplicate(t_stack *a, int value);
void				validate_and_push(t_stack *a, char *s);
void				op_sa(t_stack *a, t_bench *bench);
void				op_sb(t_stack *b, t_bench *bench);
void				op_ss(t_stack *a, t_stack *b, t_bench *bench);
void				op_pa(t_stack *a, t_stack *b, t_bench *bench);
void				op_pb(t_stack *a, t_stack *b, t_bench *bench);
void				op_ra(t_stack *a, t_bench *bench);
void				op_rb(t_stack *b, t_bench *bench);
void				op_rr(t_stack *a, t_stack *b, t_bench *bench);
void				op_rra(t_stack *a, t_bench *bench);
void				op_rrb(t_stack *b, t_bench *bench);
void				op_rrr(t_stack *a, t_stack *b, t_bench *bench);
void				sort_simple(t_stack *a, t_stack *b, t_bench *bench);
void				sort_medium(t_stack *a, t_stack *b, t_bench *bench);
void				sort_complex(t_stack *a, t_stack *b, t_bench *bench);
void				sort_adaptive(t_stack *a, t_stack *b, t_bench *bench,
						double disorder);
double				compute_disorder(t_stack *a);
double				compute_practical_disorder(t_stack *a);
void				assign_ranks(t_stack *a);
void				print_bench(t_bench *bench);

#endif
