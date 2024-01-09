/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_per.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:30:49 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:42:41 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_per_minus(t_option *op, int cnt)
{
	write(1, "%", 1);
	while (op->w > 1)
	{
		write(1, " ", 1);
		cnt++;
		op->w--;
	}
	return (cnt);
}

int	ft_print_per(t_option *op)
{
	int	cnt;

	cnt = 1;
	if (op->flag.minus == true)
		cnt = ft_print_per_minus(op, cnt);
	else
	{
		while (op->flag.zero && op->w > 1)
		{
			write(1, "0", 1);
			cnt++;
			op->w--;
		}
		while (op->w > 1)
		{
			write(1, " ", 1);
			cnt++;
			op->w--;
		}
		write(1, "%", 1);
	}
	return (cnt);
}
