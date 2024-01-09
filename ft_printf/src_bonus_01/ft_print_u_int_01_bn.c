/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_int_01_bn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:45:34 by hunpark           #+#    #+#             */
/*   Updated: 2022/10/06 13:14:38 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

int	ft_print_u_w(char *str, t_option *op)
{
	int	len;

	len = ft_strlen(str);
	if (op->flag.minus == true)
	{
		ft_putstr(str);
		while (len < op->w)
		{
			write(1, " ", 1);
			len++;
		}
	}
	else
	{
		while (len < op->w)
		{
			write(1, " ", 1);
			len++;
		}
		ft_putstr(str);
	}
	return (len);
}

int	ft_print_u(va_list *ap, t_option *op)
{
	int				cnt;
	unsigned int	num;
	char			*str;

	cnt = 0;
	num = va_arg(*ap, int);
	if (op->flag.cross == true || op->p < 0 || op->flag.plus == true
		|| op->flag.blank == true)
		return (-1);
	str = ft_uitoa_u(num, op);
	if (!str)
		return (-1);
	if ((int)ft_strlen(str) < op->w)
		cnt = ft_print_u_w(str, op);
	else
	{
		cnt = ft_strlen(str);
		ft_putstr(str);
	}
	free(str);
	return (cnt);
}
