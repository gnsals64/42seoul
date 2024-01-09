/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:21:17 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:06:31 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

int	ft_print_c_else(t_option *op, char c)
{
	int	i;

	i = 0;
	while (op->w > 1)
	{
		op->w--;
		i++;
		write(1, " ", 1);
	}
	write(1, &c, 1);
	i++;
	return (i);
}

int	ft_print_c_minus(t_option *op, char c)
{
	int	i;

	i = 0;
	if (op->w > 1)
	{
		write(1, &c, 1);
		i++;
		while ((op->w)-- > 1)
		{
			write(1, " ", 1);
			i++;
		}
	}
	else
	{
		write(1, &c, 1);
		i = 1;
	}
	return (i);
}

int	ft_print_c(va_list *ap, t_option *op)
{
	char	a;
	int		cnt;

	cnt = 0;
	a = va_arg(*ap, int);
	if (op->p != 0 || op->flag.plus == true || op->flag.zero == true
		|| op->flag.cross == true || op->flag.blank == true
		|| (op->dot == true && op->p != 0))
		return (-1);
	if (op->flag.minus == true)
		cnt = ft_print_c_minus(op, a);
	else
	{
		cnt = ft_print_c_else(op, a);
	}
	return (cnt);
}
