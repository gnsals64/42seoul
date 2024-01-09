/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:17:14 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 22:01:37 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ft_double_free(char **str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

int	ft_digit_check(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			flag = 1;
		i++;
	}
	if (flag == 1 || i == 0)
		return (-1);
	return (0);
}

int	ft_atoi_errorhandle(char *s, int *error)
{
	long long	res;
	int			sign;
	int			i;

	i = 0;
	res = 0;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (ft_digit_check(&s[i]) == -1)
		*error = 1;
	while (s[i])
	{
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	res *= sign;
	if (res > 2147483647 || res < -2147483648 || ft_strlen(s) >= 12)
		*error = 1;
	return (res);
}

char	**ft_free_save(char **save, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(save[i]);
		i++;
	}
	free(save);
	return (NULL);
}
