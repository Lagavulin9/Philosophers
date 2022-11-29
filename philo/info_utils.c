/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:47:12 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/29 10:42:42 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

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
