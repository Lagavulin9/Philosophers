/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:12:09 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/29 13:25:18 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	philo_eat(t_info *info)
{
	struct timeval	time;

	sem_wait(info->forks);
	sem_wait(info->print_sem);
	printf("%zu %d has taken a fork\n", \
	get_timestamp(&info->start), info->number);
	sem_post(info->print_sem);
	sem_wait(info->forks);
	gettimeofday(&time, 0);
	sem_wait(info->print_sem);
	gettimeofday(&info->last_eaten, 0);
	printf("%zu %d has taken a fork\n", \
	get_timestamp(&info->start), info->number);
	printf("%zu %d is eating\n", get_timestamp(&info->start), info->number);
	if (info->times_eaten++ >= info->number_must_eat)
		info->philo_is_full = 1;
	sem_post(info->print_sem);
	while (get_timestamp(&time) < info->time_to_eat)
		usleep(100);
	sem_post(info->forks);
	sem_post(info->forks);
}

static void	philo_sleep(t_info *info)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	sem_wait(info->print_sem);
	printf("%zu %d is sleeping\n", get_timestamp(&info->start), info->number);
	sem_post(info->print_sem);
	while (get_timestamp(&time) < info->time_to_sleep)
		usleep(100);
}

static void	philo_think(t_info *info)
{
	sem_wait(info->print_sem);
	printf("%zu %d is thinking\n", get_timestamp(&info->start), info->number);
	sem_post(info->print_sem);
}

static void	only_one_philo(t_info *info)
{
	sem_wait(info->forks);
	sem_wait(info->print_sem);
	printf("%zu %d has taken a fork\n", \
	get_timestamp(&info->start), info->number);
	sem_post(info->print_sem);
	sem_wait(info->forks);
}

void	routine(t_info *info)
{
	if (info->number % 2 == 0)
		usleep(info->time_to_eat * 500);
	if (info->number_of_philos == 1)
		only_one_philo(info);
	else
	{
		while (1)
		{
			philo_eat(info);
			if (info->philo_is_full)
				return ;
			philo_sleep(info);
			philo_think(info);
		}
	}
}
