/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:16:19 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/06 19:49:22 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# define STATUS_FULL 1
# define STATUS_DEAD 2

typedef struct s_info
{
	int				number;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				times_eaten;
	int				philo_is_full;
	pid_t			*pid_list;
	sem_t			*forks;
	sem_t			*print_sem;
	struct timeval	start;
	struct timeval	last_eaten;
}					t_info;

int		is_valid_input(int argc, char *argv[]);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t size);
long	get_timestamp(struct timeval *start);
int		set_info(t_info	*info, char **argv);
void	kill_all_child_proc(t_info *info);
void	sem_clear(t_info *info);
void	routine(t_info *info);

#endif