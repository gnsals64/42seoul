/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_bn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:08:57 by hunpark           #+#    #+#             */
/*   Updated: 2022/10/06 13:13:09 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

int	ft_print_s_minus(t_option *op, char *str)
{
	int	len;
	int	i;

	len = (int)ft_strlen(str);
	if (len > op->p && op->dot == true)
		len = op->p;
	i = 0;
	while (str[i] && i < op->p && op->dot == true)
		write(1, &str[i++], 1);
	while (str[i] && op->dot == false)
		write(1, &str[i++], 1);
	while (i < op->w)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}

int	ft_print_s_non(t_option *op, char *str)
{
	int		len;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	len = (int)ft_strlen(str);
	if (len > op->p && op->dot == true)
		len = op->p;
	while (len++ < op->w)
	{
		write(1, " ", 1);
		cnt++;
	}
	while (str[i] && i < op->p && op->dot == true)
	{
		write(1, &str[i++], 1);
		cnt++;
	}
	while (str[i] && op->dot == false)
	{
		write(1, &str[i++], 1);
		cnt++;
	}
	return (cnt);
}

int	ft_print_s_null(t_option *op, char *str)
{
	int	cnt;

	cnt = ft_strlen(str);
	if (op->flag.minus == true)
	{
		ft_putstr(str);
		while (op->w > cnt)
		{
			write(1, " ", 1);
			cnt++;
		}
	}
	else
	{
		while (op->w > cnt)
		{
			write(1, " ", 1);
			cnt++;
		}
		ft_putstr(str);
	}
	if (ft_strlen(str) != 6)
		free(str);
	return (cnt);
}

char	*ft_print_s_null_dot(t_option *op)
{
	char	*str;
	char	*str_null;
	int		i;

	i = 0;
	str_null = "(null)";
	str = (char *)malloc(sizeof(char) * (op->p + 1));
	if (!str)
		return (NULL);
	str[op->p] = '\0';
	while (i < op->p)
	{
		str[i] = str_null[i];
		i++;
	}
	return (str);
}

int	ft_print_s(va_list *ap, t_option *op)
{
	char	*str;
	int		cnt;
	int		null_cnt;

	null_cnt = 0;
	str = va_arg(*ap, char *);
	if (op->flag.plus == true || op->flag.zero == true || op->flag.cross == true
		|| op->p < 0)
		return (-1);
	if (str == NULL && (op->dot == false || (op->dot == true && op->p > 5)))
	{
		cnt = ft_print_s_null(op, "(null)");
		return (cnt);
	}
	else if (str == NULL && op->dot == true)
	{
		cnt = ft_print_s_null(op, ft_print_s_null_dot(op));
		return (cnt);
	}
	cnt = ft_strlen(str);
	if (op->flag.minus == true)
		cnt = ft_print_s_minus(op, str);
	else
		cnt = ft_print_s_non(op, str);
	return (cnt);
}
