/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:16:06 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/27 14:57:10 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	set_info(t_info	*info, char **argv)
{
	info->number_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->number_must_eat = 2147483647;
	if (argv[5])
		info->number_must_eat = ft_atoi(argv[5]);
	info->philo_is_dead = 0;
	info->philo_is_full = 0;
	info->index = 1;
	info->philo_ids = malloc(sizeof(pthread_t) * info->number_of_philos);
	info->forks = create_forks(info->number_of_philos);
	info->times_eaten = create_eaten_list(info);
	gettimeofday(&info->start, 0);
	info->last_eaten = create_time_list(info);
	pthread_mutex_init(&info->print_mutex, 0);
	if (!info->times_eaten || !info->last_eaten
		|| !info->philo_ids || !info->forks)
		return (-1);
	return (0);
}

void	set_philo(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->print_mutex);
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
	pthread_mutex_unlock(&info->print_mutex);
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
	pthread_mutex_destroy(&info.print_mutex);
	free(info.forks);
	free(info.philo_ids);
	free(info.times_eaten);
	free(info.last_eaten);
	return (0);
}
