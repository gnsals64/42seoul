/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 02:21:02 by hunpark           #+#    #+#             */
/*   Updated: 2023/04/30 01:33:00 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	pass_time(t_philo *philo, long time)
{
	long	now;
	long	start;

	start = ft_get_time();
	if (time == 0)
		return ;
	while (1)
	{
		now = ft_get_time();
		if ((now - start) >= time)
			break ;
		pthread_mutex_lock(&(philo->share->end));
		if (philo->share->finish == true)
		{
			pthread_mutex_unlock(&(philo->share->end));
			break ;
		}
		pthread_mutex_unlock(&(philo->share->end));
		usleep(100);
	}
}

void	dine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->share->fork[philo->left_fork]));
	ft_msg(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->share->fork[philo->right_fork]));
	ft_msg(philo, "has taken a fork");
	ft_msg(philo, "is eating");
	pthread_mutex_lock(&(philo->share->time));
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(philo->share->time));
	philo->eat_cnt++;
	pass_time(philo, philo->arg->time_eat);
	pthread_mutex_unlock(&(philo->share->fork[philo->right_fork]));
	pthread_mutex_unlock(&(philo->share->fork[philo->left_fork]));
}

void	ft_sleep(t_philo *philo)
{
	if (philo->id % 2)
		usleep(1000);
}

void	ft_sleep_msg(t_philo *philo)
{
	ft_msg(philo, "is sleeping");
	pass_time(philo, philo->arg->time_sleep);
}

void	*thread_route(void *arg)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		dine(philo);
		if (philo->arg->must_eat != -1)
		{
			if (philo->eat_cnt >= philo->arg->must_eat)
				break ;
		}
		ft_sleep_msg(philo);
		pthread_mutex_lock(&(philo->share->end));
		if (philo->share->finish == true)
		{
			pthread_mutex_unlock(&(philo->share->end));
			break ;
		}
		pthread_mutex_unlock(&(philo->share->end));
		ft_msg(philo, "is thinking");
	}
	return (NULL);
}
