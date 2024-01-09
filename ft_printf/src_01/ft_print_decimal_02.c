/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:20:19 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:42:41 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_sign(t_option *op, char *str, int n)
{
	if (n < 0)
		str[0] = '-';
	else if (n >= 0 && op->flag.blank == true)
		str[0] = ' ';
	else if (n >= 0 && op->flag.plus == true)
		str[0] = '+';
	return ;
}

char	*ft_itoa_d_p_1(int n, t_option *op)
{
	int			i;
	char		*str;
	long long	cpy;

	i = find_digit(n, 10);
	if (op->flag.plus == true || (op->flag.blank == true && n >= 0)
		|| n < 0)
		i++;
	if (n > 0)
		cpy = n;
	else
		cpy = (long long)n * -1;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (cpy > 0)
	{
		str[i--] = (cpy % 10) + 48;
		cpy /= 10;
	}
	if (n == 0)
		str[i] = 48;
	ft_sign(op, str, n);
	return (str);
}

char	*ft_itoa_d_p_2(int n, t_option *op)
{
	int			i;
	char		*str;
	long long	cpy;

	i = op->p;
	if (op->flag.plus == true || (op->flag.blank == true && n >= 0)
		|| n < 0)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n > 0)
		cpy = n;
	else
		cpy = (long long)n * -1;
	while (cpy > 0)
	{
		str[i--] = (cpy % 10) + 48;
		cpy /= 10;
	}
	while (i >= 0)
		str[i--] = '0';
	ft_sign(op, str, n);
	return (str);
}

char	*ft_itoa_d_zero(int n, t_option *op)
{
	char		*str;
	int			i;
	long long	cpy;

	i = op->w;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n > 0)
		cpy = n;
	else
		cpy = (long long)n * -1;
	while (cpy > 0)
	{
		str[i--] = (cpy % 10) + 48;
		cpy /= 10;
	}
	while (i >= 0)
		str[i--] = '0';
	ft_sign(op, str, n);
	return (str);
}

char	*ft_itoa_d(int n, t_option *op)
{
	int			i;
	char		*str;
	char		*str_zero;

	i = 0;
	if (n == 0 && op->dot == true && op->p == 0 && op->flag.plus)
		return (ft_strdup("+"));
	else if (n == 0 && op->dot == true && op->p == 0 && op->flag.blank)
		return (ft_strdup(" "));
	else if (n == 0 && op->dot == true && op->p == 0)
		return (ft_strdup(""));
	str_zero = ft_itoa(n);
	if (op->w > (int)ft_strlen(str_zero) && (op->flag.zero && op->dot == false)
		&& op->flag.minus == false)
		str = ft_itoa_d_zero(n, op);
	else if (op->p > find_digit(n, 10))
		str = ft_itoa_d_p_2(n, op);
	else
		str = ft_itoa_d_p_1(n, op);
	free(str_zero);
	return (str);
}
