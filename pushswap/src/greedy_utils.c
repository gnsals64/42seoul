/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:40:17 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 21:49:35 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ft_save_cnt(t_best *best, t_cnt *a, t_cnt *b, int *min)
{
	best->a_cnt = a->cnt;
	best->a_fn = a->fn;
	best->b_cnt = b->cnt;
	best->b_fn = b->fn;
	*min = a->cnt + b->cnt;
}

void	ft_find_direction(t_cnt *a, int i, int len, int mid)
{
	if (i > mid)
	{
		a->cnt = len - i;
		a->fn = 'b';
		return ;
	}
	a->cnt = i;
	a->fn = 'r';
}
