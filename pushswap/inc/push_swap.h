/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:06:48 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 21:49:20 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "./linked_deque.h"

typedef struct s_cnt
{
	int		cnt;
	char	fn;
}	t_cnt;

typedef struct s_best
{
	int		a_cnt;
	int		b_cnt;
	char	a_fn;
	char	b_fn;
}	t_best;

void	print_error(t_data *data);
void	success_exit(t_data *data);

void	ft_greedy(t_data *data);
void	ft_deque_b_move(t_data *data, t_best *best);
void	ft_deque_a_move(t_data *data, t_best *best);
void	ft_find_index_a(t_deque *deque, t_cnt *a, int data, int mid);
void	ft_find_best(t_data *data, t_best *best);
void	ft_save_cnt(t_best *best, t_cnt *a, t_cnt *b, int *min);
void	ft_find_direction(t_cnt *a, int i, int len, int mid);

int		ft_find_word(char *str);
int		ft_save_join(char **save, char **tmp, int *i);
int		ft_save_insert(char **save, char *av, int *i);
char	**ft_sep(int ac, char **av);
int		*ft_parsing(int ac, char **av, int *arr_len, int *error);

char	**ft_free_save(char **save, int len);
int		ft_atoi_errorhandle(char *s, int *error);
void	ft_double_free(char **str);
int		ft_digit_check(char *s);

void	ft_division(t_data *data, int a, int b, int len);
void	push_swap(t_data *data);

void	ft_sort_small(t_data *data);
void	ft_sort_three(t_data *data, int a, int b, int c);
void	ft_last_sort(t_data *data, int small);

void	ft_swap(int	*a, int *b);
void	bubble_sort(int *arr, int len, int *error, bool *sort);
void	ft_set_lst(t_data *data, int ac, char **av);

#endif
