/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:16:06 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/08 12:36:08 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

long	get_timestamp(struct timeval *start)
{
	struct timeval	now;
	long			time;

	gettimeofday(&now, 0);
	time = (now.tv_sec - start->tv_sec) * 1000;
	time += (now.tv_usec / 1000 - start->tv_usec / 1000);
	return (time);
}

void	set_philo(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->shared_mutex);
	philo->info = info;
	philo->number = info->index++;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->start = info->start;
	philo->left_fork = &info->forks[philo->number - 1];
	philo->right_fork = &info->forks[philo->number % info->number_of_philos];
	philo->only_one_philo = 0;
	if (info->number_of_philos == 1)
		philo->only_one_philo = 1;
	pthread_mutex_unlock(&info->shared_mutex);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		i;

	if (!is_valid_input(argc, argv))
		return (1);
	if (set_info(&info, argv) == -1)
		return (1);
	i = 0;
	while (i < info.number_of_philos)
		pthread_create(&info.philo_ids[i++], 0, (void *)routine, &info);
	monitor(&info);
	i = 0;
	while (i < info.number_of_philos)
		pthread_join(info.philo_ids[i++], 0);
	destroy_forks(&info);
	pthread_mutex_destroy(&info.shared_mutex);
	free(info.forks);
	free(info.philo_ids);
	free(info.times_eaten);
	free(info.last_eaten);
	return (0);
}
