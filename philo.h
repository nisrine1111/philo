/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:44:15 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 02:42:17 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	int				number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_meals;
	int				meal_check;
	long long		start_time;
	int				ready;
	int				over;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	over_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	long long		thread_start;
	pthread_t		life_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_monitor_args
{
	t_data	*data;
	t_philo	*philo;
}	t_monitor_args;

int			ft_parse_args(char ac, char **av, t_data *data);
int			ft_is_digit(char *str);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data, t_philo *philos);
int			start_simulation(t_data *data, t_philo *philo);
int			philo_died(t_philo *philo);
int			simulation_monitor(t_data *data, t_philo *philo);
int			ft_usleep(long long time, t_philo *philo);
int			ft_print_error(char *msg);
int			destroy_mutexes(t_data *data, t_philo *philo, pthread_t *monitor);
void		*ft_philo_routine(void *param);
void		*monitor_thread(void *arg);
void		print_status(t_philo *philo, char *msg);
int			is_over(t_philo *philo);
int			is_ready(t_philo *philo);
long long	ft_atoi(const char *str);
long long	current_time(void);
#endif
