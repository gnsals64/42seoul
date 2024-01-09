/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_int_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:58:09 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:42:41 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_uitoa_u_p_1(unsigned int n)
{
	int			i;
	char		*str;

	i = find_digit(n, 10);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i--] = (n % 10) + 48;
		n /= 10;
	}
	if (n == 0)
		str[i] = 48;
	return (str);
}

char	*ft_uitoa_u_p_2(unsigned int n, t_option *op)
{
	int			i;
	char		*str;

	i = op->p;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i--] = (n % 10) + 48;
		n /= 10;
	}
	while (i >= 0)
		str[i--] = '0';
	return (str);
}

char	*ft_uitoa_u_zero(unsigned int n, t_option *op)
{
	char		*str;
	int			i;

	i = op->w;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i--] = (n % 10) + 48;
		n /= 10;
	}
	while (i >= 0)
		str[i--] = '0';
	return (str);
}

char	*ft_uitoa_u(unsigned int n, t_option *op)
{
	int			i;
	char		*str;
	char		*str_zero;

	i = 0;
	if (n == 0 && op->dot == true && op->p == 0)
		return (ft_strdup(""));
	str_zero = ft_uitoa(n);
	if (!str_zero)
		return (NULL);
	if (op->w > (int)ft_strlen(str_zero) && (op->flag.zero && op->dot == false)
		&& op->flag.minus == false)
		str = ft_uitoa_u_zero(n, op);
	else if (op->p > find_digit(n, 10))
		str = ft_uitoa_u_p_2(n, op);
	else
		str = ft_uitoa_u_p_1(n);
	free(str_zero);
	return (str);
}
