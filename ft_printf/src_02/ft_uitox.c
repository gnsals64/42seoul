/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:56:22 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:42:41 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_uitox_u(unsigned int n, t_option *op)
{
	int			i;
	char		*str;

	i = find_digit_hex(n);
	if (n == 0 && op->dot == false)
		return (ft_strdup("0"));
	if (n == 0 && op->dot == true)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i--] = ft_find_hex("0123456789abcdef", (n % 16));
		n /= 16;
	}
	return (str);
}

char	*ft_uitox_u_l(unsigned int n, t_option *op)
{
	int			i;
	char		*str;

	i = find_digit_hex(n);
	if (n == 0 && op->dot == false)
		return (ft_strdup("0"));
	if (n == 0 && op->dot == true && op->p == 0)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i--] = ft_find_hex("0123456789ABCDEF", (n % 16));
		n /= 16;
	}
	return (str);
}
