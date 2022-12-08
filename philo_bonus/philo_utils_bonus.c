/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:43:00 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/07 11:30:46 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

long	get_timestamp(struct timeval *start)
{
	struct timeval	now;
	long			time;

	gettimeofday(&now, 0);
	time = (now.tv_sec - start->tv_sec) * 1000;
	time += (now.tv_usec / 1000 - start->tv_usec / 1000);
	return (time);
}

int	set_info(t_info	*info, char **argv)
{
	sem_unlink("forks");
	sem_unlink("shared_sem");
	info->number_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->number_must_eat = 2147483647;
	if (argv[5])
		info->number_must_eat = ft_atoi(argv[5]);
	info->pid_list = ft_calloc(sizeof(pid_t) * info->number_of_philos);
	info->forks = sem_open("forks", O_CREAT, 0644, info->number_of_philos);
	info->shared_sem = sem_open("shared_sem", O_CREAT, 0644, 1);
	info->number = 1;
	info->times_eaten = 0;
	info->philo_is_full = 0;
	gettimeofday(&info->start, 0);
	info->last_eaten = info->start;
	return (0);
}

void	kill_all_child_proc(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philos)
		kill(info->pid_list[i++], SIGKILL);
}

void	sem_clear(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->shared_sem);
	sem_unlink("forks");
	sem_unlink("shared_sem");
}
