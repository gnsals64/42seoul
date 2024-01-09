/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_swap_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:51:18 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 21:49:37 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	sa(t_data *data)
{
	if (data->deque_a->cnt < 2)
		return ;
	ft_swap(&(data->deque_a->head->data), &(data->deque_a->head->next->data));
	write(1, "sa\n", 3);
}

void	sb(t_data *data)
{
	if (data->deque_b->cnt < 2)
		return ;
	ft_swap(&(data->deque_b->head->data), &(data->deque_b->head->next->data));
	write(1, "sb\n", 3);
}

void	pa(t_data *data)
{
	int	tmp;

	if (data->deque_b->head != NULL)
	{
		tmp = data->deque_b->head->data;
		pop_front(data->deque_b);
		push_front(data->deque_a, tmp);
		write(1, "pa\n", 3);
	}
}

void	pb(t_data *data)
{
	int	tmp;

	if (data->deque_a->head != NULL)
	{
		tmp = data->deque_a->head->data;
		pop_front(data->deque_a);
		push_front(data->deque_b, tmp);
		write(1, "pb\n", 3);
	}
}
