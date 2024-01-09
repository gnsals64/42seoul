/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:12:07 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/23 15:43:57 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	print_error(t_data *data)
{
	if (data->deque_a != NULL)
	{
		while (data->deque_a->head != NULL)
			pop_front(data->deque_a);
		free(data->deque_a);
	}
	if (data->deque_b != NULL)
	{
		while (data->deque_b->head != NULL)
			pop_front(data->deque_b);
		free(data->deque_b);
	}
	if (data->arr != NULL)
		free(data->arr);
	free(data);
	write(2, "error\n", 6);
	exit(1);
}

void	success_exit(t_data *data)
{
	if (data->deque_a != NULL)
	{
		while (data->deque_a->head != NULL)
			pop_front(data->deque_a);
		free(data->deque_a);
	}
	if (data->deque_b != NULL)
	{
		while (data->deque_b->head != NULL)
			pop_front(data->deque_b);
		free(data->deque_b);
	}
	free(data->arr);
	free(data);
}
