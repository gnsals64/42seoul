/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:04:48 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 14:55:44 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ft_sort_small(t_data *data)
{
	int	a;
	int	b;
	int	c;

	if (data->deque_a->cnt == 3)
	{
		a = data->deque_a->head->data;
		b = data->deque_a->head->next->data;
		c = data->deque_a->head->next->next->data;
		ft_sort_three(data, a, b, c);
	}
	else if (data->deque_a->cnt == 2)
	{
		a = data->deque_a->head->data;
		b = data->deque_a->head->next->data;
		if (a > b)
			ra(data);
	}
}

void	ft_sort_three(t_data *data, int a, int b, int c)
{
	if (c > a && a > b)
		sa(data);
	else if (a > b && b > c)
	{
		sa(data);
		rra(data);
	}
	else if (a > c && c > b)
		ra(data);
	else if (b > c && c > a)
	{
		sa(data);
		ra(data);
	}
	else if (b > a && a > c)
		rra(data);
}

void	ft_last_sort(t_data *data, int small)
{
	int		r;
	int		rr;
	t_node	*head;
	t_node	*tail;

	r = 0;
	rr = 0;
	head = data->deque_a->head;
	tail = data->deque_a->tail;
	while (head->data != small)
	{
		head = head->next;
		r++;
	}
	while (tail->data != small)
	{
		tail = tail->prev;
		rr++;
	}
	if (rr > r)
		while (data->deque_a->head->data != small)
			ra(data);
	else
		while (data->deque_a->head->data != small)
			rra(data);
}
