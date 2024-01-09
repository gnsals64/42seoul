/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:09:25 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/23 14:37:05 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ft_division(t_data *data, int a, int b, int len)
{
	int	i;

	i = 0;
	while (i < len && data->deque_a->cnt > 3)
	{
		if (data->deque_a->head->data < b)
		{
			if (data->deque_a->head->data < a && data->deque_b->head != NULL)
			{
				pb(data);
				rb(data);
			}
			else
				pb(data);
		}
		else
			ra(data);
		i++;
	}
	while (data->deque_a->cnt > 3)
	{
		pb(data);
	}
}

void	push_swap(t_data *data)
{
	int	a;
	int	b;

	if (data->sort == true)
		return ;
	a = data->arr[(data->deque_a->cnt) / 3];
	b = data->arr[(data->deque_a->cnt) / 3 * 2];
	ft_division(data, a, b, data->deque_a->cnt);
	ft_sort_small(data);
	while (data->deque_b->head != NULL)
		ft_greedy(data);
	ft_last_sort(data, data->arr[0]);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_memset(data, 0, sizeof(t_data));
	data->sort = true;
	ft_set_lst(data, ac, av);
	push_swap(data);
	success_exit(data);
	return (0);
}
