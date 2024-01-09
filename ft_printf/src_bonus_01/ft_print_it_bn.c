/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_it.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:19:09 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:33:13 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

int	ft_print_it(va_list *ap, t_option *op, int word_cnt)
{
	int	i;

	i = 0;
	if (op->t == 'c')
		i = ft_print_c(ap, op);
	else if (op->t == 's')
		i = ft_print_s(ap, op);
	else if (op->t == 'p')
		i = ft_print_p(ap, op);
	else if (op->t == 'd' || op->t == 'i')
		i = ft_print_d(ap, op);
	else if (op->t == 'u')
		i = ft_print_u(ap, op);
	else if (op->t == 'x')
		i = ft_print_x(ap, op);
	else if (op->t == 'X')
		i = ft_print_x_l(ap, op);
	else if (op->t == '%')
		i = ft_print_per(op);
	if (i == -1)
		i = 0;
	word_cnt += i;
	return (word_cnt);
}
