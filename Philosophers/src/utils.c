/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:00:59 by hunpark           #+#    #+#             */
/*   Updated: 2023/04/28 20:06:42 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	sign = 1;
	res = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while ((s[i] >= 48 && s[i] <= 57) && s[i])
	{
		res = res * 10 + s[i] - 48;
		i++;
	}
	return (sign * res);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

void	ft_free(t_philo *philo)
{
	free(philo->share);
	free(philo);
}
