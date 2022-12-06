/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:12:09 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/06 19:19:50 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->info->print_mutex);
	if (!philo->info->philo_is_dead && !philo->info->philo_is_full)
		printf("%zu %d has taken a fork\n", \
		get_timestamp(&philo->start), philo->number);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->info->print_mutex);
	gettimeofday(&time, 0);
	if (!philo->info->philo_is_dead && !philo->info->philo_is_full)
	{
		printf("%zu %d has taken a fork\n", \
			get_timestamp(&philo->start), philo->number);
		printf("%zu %d is eating\n", \
			get_timestamp(&philo->start), philo->number);
	}
	philo->info->times_eaten[philo->number - 1]++;
	gettimeofday(&philo->info->last_eaten[philo->number - 1], 0);
	pthread_mutex_unlock(&philo->info->print_mutex);
	while (get_timestamp(&time) < philo->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->info->print_mutex);
	gettimeofday(&time, 0);
	if (!philo->info->philo_is_dead && !philo->info->philo_is_full)
		printf("%zu %d is sleeping\n", \
		get_timestamp(&philo->start), philo->number);
	pthread_mutex_unlock(&philo->info->print_mutex);
	while (get_timestamp(&time) < philo->time_to_sleep)
		usleep(100);
}

static void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (!philo->info->philo_is_dead && !philo->info->philo_is_full)
		printf("%zu %d is thinking\n", \
		get_timestamp(&philo->start), philo->number);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

static void	only_one_philo(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->info->print_mutex);
	gettimeofday(&time, 0);
	if (!philo->info->philo_is_dead && !philo->info->philo_is_full)
		printf("%zu %d has taken a fork\n", \
		get_timestamp(&philo->start), philo->number);
	pthread_mutex_unlock(&philo->info->print_mutex);
	while (get_timestamp(&time) <= philo->time_to_die)
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
}

void	routine(t_info *info)
{
	t_philo	philo;

	set_philo(&philo, info);
	if (philo.number % 2 == 0)
		usleep(philo.time_to_eat * 500);
	if (philo.only_one_philo)
		only_one_philo(&philo);
	else
	{
		while (1)
		{
			philo_eat(&philo);
			philo_sleep(&philo);
			philo_think(&philo);
			pthread_mutex_lock(&philo.info->print_mutex);
			if (philo.info->philo_is_dead || philo.info->philo_is_full)
				break ;
			pthread_mutex_unlock(&philo.info->print_mutex);
		}
		pthread_mutex_unlock(&philo.info->print_mutex);
	}
}
