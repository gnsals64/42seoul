/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:37:04 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 21:49:34 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ft_greedy(t_data *data)
{
	int		tmp;
	t_best	best;

	tmp = data->deque_b->head->data;
	ft_find_best(data, &best);
	ft_deque_b_move(data, &best);
	ft_deque_a_move(data, &best);
	pa(data);
}

void	ft_deque_b_move(t_data *data, t_best *best)
{
	if (best->b_fn == 'r' && best->b_cnt != 0)
	{
		while (best->b_cnt)
		{
			rb(data);
			best->b_cnt--;
		}
	}
	else if (best->b_fn == 'b' && best->b_cnt != 0)
	{
		while (best->b_cnt)
		{
			rrb(data);
			best->b_cnt--;
		}
	}
}

void	ft_deque_a_move(t_data *data, t_best *best)
{
	if (best->a_fn == 'r' && best->a_cnt != 0)
	{
		while (best->a_cnt)
		{
			ra(data);
			best->a_cnt--;
		}
	}
	else if (best->a_fn == 'b' && best->a_cnt != 0)
	{
		while (best->a_cnt)
		{
			rra(data);
			best->a_cnt--;
		}
	}
}

void	ft_find_index_a(t_deque *deque, t_cnt *a, int data, int mid)
{
	int		i;
	int		start;
	int		end;
	t_node	*head;

	i = 0;
	head = deque->head;
	while (i < deque->cnt)
	{
		start = head->data;
		end = head->next->data;
		if (head->next->next != NULL)
			head = head->next;
		i++;
		if (data < start && data < end && start > end)
			break ;
		if (data > start && data > end && start > end)
			break ;
		if (data > start && data < end)
			break ;
	}
	ft_find_direction(a, i, deque->cnt, mid);
}

void	ft_find_best(t_data *data, t_best *best)
{
	t_node	*head;
	t_cnt	a;
	t_cnt	b;
	int		tmp;
	int		min;

	b.cnt = 0;
	b.fn = 'r';
	min = 10000;
	head = data->deque_b->head;
	while (head != NULL)
	{
		tmp = b.cnt;
		ft_find_index_a(data->deque_a, &a, head->data, data->deque_a->cnt / 2);
		if (b.cnt > data->deque_b->cnt / 2)
		{
			b.cnt = data->deque_b->cnt - tmp;
			b.fn = 'b';
		}
		if (a.cnt + b.cnt < min)
			ft_save_cnt(best, &a, &b, &min);
		b.cnt = tmp;
		b.cnt++;
		head = head->next;
	}
}
