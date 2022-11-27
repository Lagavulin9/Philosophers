/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:43:00 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/27 14:29:25 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

int	is_philo_dead(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
	{
		if (get_timestamp(&info->last_eaten[i]) > info->time_to_die)
		{
			info->philo_is_dead = 1;
			printf("%zu %d died\n", get_timestamp(&info->start), i + 1);
			pthread_mutex_unlock(&info->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_philo_full(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
	{
		if (info->times_eaten[i] <= info->number_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	monitor(t_info *info)
{
	while (1)
	{
		pthread_mutex_lock(&info->print_mutex);
		if (is_philo_dead(info))
		{
			pthread_mutex_unlock(&info->print_mutex);
			return ;
		}
		pthread_mutex_unlock(&info->print_mutex);
		pthread_mutex_lock(&info->print_mutex);
		if (is_philo_full(info))
		{
			info->philo_is_full = 1;
			pthread_mutex_unlock(&info->print_mutex);
			return ;
		}
		pthread_mutex_unlock(&info->print_mutex);
	}
}
