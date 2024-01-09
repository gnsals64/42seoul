/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_mix_bn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:36:44 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/23 15:37:45 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ss(t_data *data)
{
	sa(data);
	sb(data);
}

void	rr(t_data *data)
{
	ra(data);
	rb(data);
}

void	rrr(t_data *data)
{
	rra(data);
	rrb(data);
}

void	run_swap_push(t_data *data, char *buf, bool *flag)
{
	if (ft_strncmp(buf, "sa\n", 5) == 0)
		sa(data);
	else if (ft_strncmp(buf, "sb\n", 5) == 0)
		sb(data);
	else if (ft_strncmp(buf, "ss\n", 5) == 0)
		ss(data);
	else if (ft_strncmp(buf, "pa\n", 5) == 0)
		pa(data);
	else if (ft_strncmp(buf, "pb\n", 5) == 0)
		pb(data);
	else if (buf == NULL)
		return ;
	else
		*flag = false;
}

void	run_rotate(t_data *data, char *buf, bool *flag)
{
	if (ft_strncmp(buf, "ra\n", 5) == 0)
		ra(data);
	else if (ft_strncmp(buf, "rb\n", 5) == 0)
		rb(data);
	else if (ft_strncmp(buf, "rra\n", 5) == 0)
		rra(data);
	else if (ft_strncmp(buf, "rrb\n", 5) == 0)
		rrb(data);
	else if (ft_strncmp(buf, "rr\n", 5) == 0)
		rr(data);
	else if (ft_strncmp(buf, "rrr\n", 5) == 0)
		rrr(data);
	else if (buf == NULL)
		return ;
	else
		*flag = false;
}
