/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:05:43 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 21:49:37 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ra(t_data *data)
{
	int	tmp;

	if (data->deque_a->cnt < 2)
		return ;
	tmp = data->deque_a->head->data;
	pop_front(data->deque_a);
	push_back(data->deque_a, tmp);
	write(1, "ra\n", 3);
}

void	rb(t_data *data)
{
	int	tmp;

	if (data->deque_b->cnt < 2)
		return ;
	tmp = data->deque_b->head->data;
	pop_front(data->deque_b);
	push_back(data->deque_b, tmp);
	write(1, "rb\n", 3);
}

void	rra(t_data *data)
{
	int	tmp;

	if (data->deque_a->cnt < 2)
		return ;
	tmp = data->deque_a->tail->data;
	pop_back(data->deque_a);
	push_front(data->deque_a, tmp);
	write(1, "rra\n", 4);
}

void	rrb(t_data *data)
{
	int	tmp;

	if (data->deque_b->cnt < 2)
		return ;
	tmp = data->deque_b->tail->data;
	pop_back(data->deque_b);
	push_front(data->deque_b, tmp);
	write(1, "rrb\n", 4);
}
