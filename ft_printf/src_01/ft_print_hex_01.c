/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:42:04 by hunpark           #+#    #+#             */
/*   Updated: 2022/10/06 13:09:44 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_uitoa_x_zero(t_option *op, char *str_zero)
{
	char		*str;
	int			i;
	char		*join_str;

	i = op->p - ft_strlen(str_zero);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (i >= 0)
		str[i--] = '0';
	join_str = ft_strjoin(str, str_zero);
	free (str);
	return (join_str);
}

char	*ft_uitox(unsigned int n, t_option *op, int flag)
{
	int			i;
	char		*str;
	char		*str_zero;

	i = 0;
	if (flag == 0)
		str_zero = ft_uitox_u(n, op);
	else if (flag == 1)
		str_zero = ft_uitox_u_l(n, op);
	if (!str_zero)
		return (NULL);
	if (op->p > (int)ft_strlen(str_zero) && op->dot == true)
		str = ft_uitoa_x_zero(op, str_zero);
	else
		return (str_zero);
	free(str_zero);
	return (str);
}

int	ft_print_x(va_list *ap, t_option *op)
{
	int				cnt;
	unsigned int	num;
	char			*str;

	cnt = 0;
	num = va_arg(*ap, int);
	if (op->p < 0 || op->flag.plus == true || op->flag.blank == true)
		return (-1);
	str = ft_uitox(num, op, 0);
	if (!str)
		return (-1);
	cnt = ft_print_x_w(str, op, 0, num);
	free(str);
	return (cnt);
}

int	ft_print_x_l(va_list *ap, t_option *op)
{
	int				cnt;
	unsigned int	num;
	char			*str;

	cnt = 0;
	num = va_arg(*ap, int);
	if (op->p < 0 || op->flag.plus == true || op->flag.blank == true)
		return (-1);
	str = ft_uitox(num, op, 1);
	if (!str)
		return (-1);
	cnt = ft_print_x_w(str, op, 1, num);
	free(str);
	return (cnt);
}
