/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:55:38 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/16 15:51:45 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	bubble_sort(int *arr, int len, int *error, bool *sort)
{
	int	i;
	int	j;

	i = -1;
	if (arr == NULL)
		return ;
	while (++i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				ft_swap(&arr[j], &arr[j + 1]);
				*sort = false;
			}
			j++;
		}
	}
	i = -1;
	while (++i < len - 1)
	{
		if (arr[i] == arr[i + 1])
			*error = 1;
	}
}

void	ft_set_lst(t_data *data, int ac, char **av)
{
	int		i;
	int		len;
	int		*arr;
	int		error;

	i = -1;
	len = 0;
	error = 0;
	arr = ft_parsing(ac, av, &len, &error);
	data->arr = ft_parsing(ac, av, &len, &error);
	bubble_sort(data->arr, len, &error, &(data->sort));
	if (!arr || !(data->arr) || error == 1)
	{
		if (arr != NULL)
			free(arr);
		print_error(data);
	}
	data->deque_a = init_info();
	data->deque_b = init_info();
	if (data->deque_a == NULL || data->deque_b == NULL)
		return ;
	while (++i < len)
		push_back(data->deque_a, arr[i]);
	free(arr);
}

void	ft_swap(int	*a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}
