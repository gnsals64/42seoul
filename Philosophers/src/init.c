/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:26:51 by hunpark           #+#    #+#             */
/*   Updated: 2023/04/30 01:55:14 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	check_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (-1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0
		|| ft_atoi(argv[3]) == 0 || ft_atoi(argv[4]) == 0)
		return (-1);
	if (argv[5] != NULL)
	{
		if (ft_atoi(argv[5]) == 0)
			return (-1);
	}
	return (0);
}

int	mutex_init(t_share *share)
{
	if (pthread_mutex_init(&(share->print), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(share->time), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(share->end), NULL) != 0)
		return (-1);
	return (0);
}

int	init_share(t_share *share, t_arg *arg)
{
	int	i;

	i = 0;
	share->fork = malloc(sizeof(pthread_mutex_t) * arg->num);
	if (!share->fork)
		return (-1);
	while (i < arg->num)
	{
		if (pthread_mutex_init(&(share->fork[i]), NULL) != 0)
		{
			free(share->fork);
			printf("mutex_init_error\n");
			return (-1);
		}
		i++;
	}
	if (mutex_init(share) == -1)
	{
		free(share->fork);
		printf("mutex_init_error\n");
		return (-1);
	}
	share->time_to_start = ft_get_time();
	share->finish = false;
	return (0);
}

int	init_philo(t_philo **philo, t_arg *arg, t_share *share)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->num);
	if (!(*philo))
	{
		free(share);
		return (-1);
	}
	while (i < arg->num)
	{
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].id = i;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + arg->num - 1) % arg->num;
		(*philo)[i].last_eat = ft_get_time();
		(*philo)[i].arg = arg;
		(*philo)[i].share = share;
		i++;
	}
	return (0);
}

void	init_arg(t_arg *arg, char **argv)
{
	arg->num = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = -1;
}
