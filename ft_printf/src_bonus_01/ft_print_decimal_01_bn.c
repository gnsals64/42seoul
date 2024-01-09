/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal_01_bn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:51:03 by hunpark           #+#    #+#             */
/*   Updated: 2022/10/06 13:11:39 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

int	ft_print_d_minus(char *str, t_option *op)
{
	int	cnt;

	cnt = ft_strlen(str);
	ft_putstr(str);
	while (op->w > cnt)
	{
		write(1, " ", 1);
		cnt++;
	}
	return (cnt);
}

int	ft_print_d_else(char *str, t_option *op)
{
	int	cnt;

	cnt = ft_strlen(str);
	while (op->w > cnt)
	{
		write(1, " ", 1);
		cnt++;
	}
	ft_putstr(str);
	return (cnt);
}

int	ft_print_d_w(char *str, t_option *op)
{
	int	cnt;

	if (op->flag.minus == true)
		cnt = ft_print_d_minus(str, op);
	else
		cnt = ft_print_d_else(str, op);
	return (cnt);
}

int	ft_print_d(va_list *ap, t_option *op)
{
	int		num;
	int		cnt;
	char	*str;

	cnt = 0;
	num = va_arg(*ap, int);
	if (op->flag.cross == true || op->p < 0 || (op->flag.blank == true
			&& op->flag.plus == true))
		return (-1);
	str = ft_itoa_d(num, op);
	if (!str)
		return (-1);
	if ((int)ft_strlen(str) < op->w)
		cnt = ft_print_d_w(str, op);
	else
	{
		cnt = ft_strlen(str);
		ft_putstr(str);
	}
	free (str);
	return (cnt);
}
