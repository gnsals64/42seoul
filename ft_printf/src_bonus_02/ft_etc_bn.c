/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_etc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:16:33 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:06:55 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/ft_printf_bonus.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

char	*ft_fill_space(int w)
{
	char	*save;

	save = (char *)malloc(sizeof(char) * (w + 1));
	ft_memset(save, ' ', w);
	save[w] = '\0';
	return (save);
}

void	ft_else_write(char *str, int *word_cnt, int *i)
{
	write(1, &str[*i], 1);
	(*i)++;
	(*word_cnt)++;
}

int	find_digit(long long num, int n)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= n;
		i++;
	}
	return (i);
}

int	find_digit_hex(unsigned long long num)
{
	int	i;

	i = 0;
	while (num > 0)
	{
		num /= 16;
		i++;
	}
	return (i);
}
