/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 02:39:13 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:42:41 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_x_w_minus(char *str, t_option *op, int flag, unsigned int num)
{
	char	*save;
	int		len;

	if (op->flag.cross == true && num != 0)
	{
		if (flag == 0)
			save = ft_strjoin("0x", str);
		else
			save = ft_strjoin("0X", str);
	}
	else
		save = ft_strdup(str);
	len = ft_strlen(save);
	ft_putstr(save);
	while (len < op->w)
	{
		write(1, " ", 1);
		len++;
	}
	free(save);
	return (len);
}

int	ft_print_x_w_else(char *str, t_option *op, int flag, unsigned int num)
{
	char	*save;
	int		len;

	if (op->flag.cross == true && num != 0)
	{
		if (flag == 0)
			save = ft_strjoin("0x", str);
		else
			save = ft_strjoin("0X", str);
	}
	else
		save = ft_strdup(str);
	len = ft_strlen(save);
	while (len < op->w)
	{
		write(1, " ", 1);
		len++;
	}
	ft_putstr(save);
	free(save);
	return (len);
}

int	ft_print_x_w_zero(char *str, t_option *op, int flag, unsigned int num)
{
	int		len;

	len = ft_strlen(str);
	if (op->flag.cross && flag == 0 && num != 0)
	{
		write(1, "0x", 2);
		op->w -= 2;
	}
	else if (op->flag.cross && flag == 1 && num != 0)
	{
		write(1, "0X", 2);
		op->w -= 2;
	}
	while (len < op->w)
	{
		write(1, "0", 1);
		len++;
	}
	if (op->flag.cross && num != 0)
		len += 2;
	ft_putstr(str);
	return (len);
}

int	ft_print_x_w(char *str, t_option *op, int flag, unsigned int num)
{
	int	len;

	len = ft_strlen(str);
	if (op->flag.minus == true)
		len = ft_print_x_w_minus(str, op, flag, num);
	else if (op->flag.minus == false && op->flag.zero == true
		&& op->dot == false)
		len = ft_print_x_w_zero(str, op, flag, num);
	else
		len = ft_print_x_w_else(str, op, flag, num);
	return (len);
}
