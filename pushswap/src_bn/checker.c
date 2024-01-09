/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:55:53 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/23 15:44:50 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/checker.h"

void	sort_check(t_data *data)
{
	int		i;
	t_node	*head;

	i = 0;
	head = data->deque_a->head;
	if (data->deque_b->head != NULL)
	{
		write(2, "KO\n", 3);
		return ;
	}
	while (head != NULL)
	{
		if (head->data != data->arr[i])
		{
			write(1, "KO\n", 3);
			return ;
		}
		head = head->next;
		i++;
	}
	write(1, "OK\n", 3);
}

void	checker(t_data *data)
{
	char	*buf;
	bool	flag1;
	bool	flag2;

	buf = get_next_line(0);
	while (buf != NULL)
	{
		flag1 = true;
		flag2 = true;
		run_swap_push(data, buf, &flag1);
		run_rotate(data, buf, &flag2);
		free(buf);
		if (flag1 == false && flag2 == false)
			print_error(data);
		buf = get_next_line(0);
	}
	sort_check(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 2)
		return (0);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_memset(data, 0, sizeof(t_data));
	data->sort = true;
	ft_set_lst(data, ac, av);
	checker(data);
	success_exit(data);
	return (0);
}
