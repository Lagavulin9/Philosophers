/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:16:06 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/29 13:37:12 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

static void	monitor(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i++ < info->number_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == STATUS_DEAD)
			kill_all_child_proc(info);
	}
}

static void	child_process(t_info *info)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, 0, (void *)routine, info);
	while (1)
	{
		sem_wait(info->print_sem);
		if (info->philo_is_full)
			break ;
		if (get_timestamp(&info->last_eaten) > info->time_to_die)
		{
			printf("%zu %d died\n", get_timestamp(&info->start), info->number);
			exit(STATUS_DEAD);
		}
		sem_post(info->print_sem);
	}
	sem_post(info->print_sem);
	pthread_join(thread_id, 0);
	exit(STATUS_FULL);
}

int	main(int argc, char **argv)
{
	t_info	info;
	pid_t	pid;
	int		i;

	if (!is_valid_input(argc, argv) || set_info(&info, argv) == -1)
		return (1);
	i = 0;
	while (i < info.number_of_philos)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			child_process(&info);
		else
		{
			info.pid_list[i++] = pid;
			info.number++;
		}
	}
	monitor(&info);
	sem_clear(&info);
	return (0);
}
