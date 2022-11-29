/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:16:19 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/28 11:14:09 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				philo_is_dead;
	int				philo_is_full;
	int				index;
	struct timeval	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_t		*philo_ids;
	int				*times_eaten;
	struct timeval	*last_eaten;
}					t_info;

typedef struct s_philo
{
	t_info			*info;
	int				number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				only_one_philo;
	struct timeval	start;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

long			get_timestamp(struct timeval *start);
void			set_philo(t_philo *philo, t_info *info);
int				set_info(t_info	*info, char **argv);
pthread_mutex_t	*create_forks(int num);
void			destroy_forks(t_info *info);
struct timeval	*create_time_list(t_info *info);
int				*create_eaten_list(t_info *info);
int				is_valid_input(int argc, char *argv[]);
int				ft_atoi(const char *str);
void			monitor(t_info *info);
void			routine(t_info *info);

#endif