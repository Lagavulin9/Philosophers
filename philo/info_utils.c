/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:47:12 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/27 14:42:48 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
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

pthread_mutex_t	*create_forks(int num)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * num);
	i = 0;
	while (i < num)
		pthread_mutex_init(&forks[i++], 0);
	return (forks);
}

void	destroy_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
		pthread_mutex_destroy(&info->forks[i++]);
}

struct timeval	*create_time_list(t_info *info)
{
	struct timeval	*list;
	int				i;

	list = malloc(sizeof(struct timeval) * info->number_of_philos);
	if (list)
	{
		i = 0;
		while (i < info->number_of_philos)
			list[i++] = info->start;
	}
	return (list);
}

int	*create_eaten_list(t_info *info)
{
	int	*list;
	int	i;

	list = malloc(sizeof(int) * info->number_of_philos);
	if (list)
	{
		i = 0;
		while (i < info->number_of_philos)
			list[i++] = 0;
	}
	return (list);
}
