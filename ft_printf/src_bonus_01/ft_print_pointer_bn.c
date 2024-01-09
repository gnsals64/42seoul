/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:39:58 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:06:45 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

char	ft_find_hex(char *base, int num)
{
	int		i;
	char	c;

	i = 0;
	while (base[i])
	{
		if (i == num)
			c = base[i];
		i++;
	}
	return (c);
}

char	*ft_convert_base_p(unsigned long long num, char *base)
{
	char	*str;
	int		len;

	len = find_digit_hex(num) + 2;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	str[len] = '\0';
	while (num > 0)
	{
		str[len - 1] = ft_find_hex(base, (num % 16));
		len--;
		num /= 16;
	}
	return (str);
}

int	ft_print_p_minus(char *str, t_option *op)
{
	int	len;

	len = (int)ft_strlen(str);
	if (op->w > len)
	{
		ft_putstr(str);
		while (op->w > len)
		{
			write(1, " ", 1);
			len++;
		}
	}
	else
		ft_putstr(str);
	return (len);
}

int	ft_print_p_else(char *str, t_option *op)
{
	int	len;

	len = (int)ft_strlen(str);
	if (op->w > len)
	{
		while (op->w > len)
		{
			write(1, " ", 1);
			len++;
		}
		ft_putstr(str);
	}
	else
		ft_putstr(str);
	return (len);
}

int	ft_print_p(va_list *ap, t_option *op)
{
	unsigned long long	pointer;
	int					cnt;
	char				*str;

	if (op->flag.plus == true || op->flag.zero == true || op->flag.cross == true
		|| op->flag.blank == true || op->dot == true)
		return (-1);
	cnt = 0;
	pointer = (unsigned long long)va_arg(*ap, char *);
	if (pointer == 0)
		str = ft_strdup("0x0");
	else
		str = ft_convert_base_p(pointer, "0123456789abcdef");
	if (!str)
		return (-1);
	if (op->flag.minus == true)
		cnt += ft_print_p_minus(str, op);
	else
		cnt += ft_print_p_else(str, op);
	free(str);
	return (cnt);
}
