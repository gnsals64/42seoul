/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:29:08 by hunpark           #+#    #+#             */
/*   Updated: 2022/10/06 12:29:27 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_flag_on(t_option *op, char a)
{
	if (a == '-')
		op->flag.minus = true;
	else if (a == '+')
		op->flag.plus = true;
	else if (a == '#')
		op->flag.cross = true;
	else if (a == ' ')
		op->flag.blank = true;
	else if (a == '0')
		op->flag.zero = true;
}

void	ft_sep(t_option *op, char *str)
{
	int	i;

	i = 0;
	ft_bzero(op, sizeof(t_option));
	while (ft_isflag(str[i]) && str[i])
	{
		ft_flag_on(op, str[i]);
		i++;
	}
	if (ft_isdigit(str[i]) && str[i])
		i += ft_width_precision_check(op, str, i, 0);
	if (str[i] == '.' && str[i])
		i += ft_width_precision_check(op, str, i + 1, 1) + 1;
	if (ft_istype(str[i]) && str[i])
		op->t = str[i];
}

int	ft_parsing(char *input, t_option *op, int i)
{
	char	*str;
	int		end_i;

	end_i = i;
	while (!(ft_istype(input[end_i])) && input[end_i])
		end_i++;
	if (input[end_i] == '\0')
		return (-1);
	str = ft_substr(input, i, end_i - i + 1);
	if (!str)
		return (-1);
	ft_sep(op, str);
	free(str);
	if (op->p < 0)
		return (-1);
	i = end_i + 1;
	return (i);
}

int	ft_width_precision_check(t_option *op, char *str, int i, int flag)
{
	char	*save;
	int		end_i;

	end_i = i;
	while (ft_isdigit(str[end_i]))
		end_i++;
	save = ft_substr(str, i, end_i - i);
	if (flag == 0)
		op->w = ft_atoi(save);
	else if (flag == 1)
	{
		op->p = ft_atoi(save);
		op->dot = true;
	}
	end_i = ft_strlen(save);
	free(save);
	return (end_i);
}
