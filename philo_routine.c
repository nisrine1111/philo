/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:56:27 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 02:08:22 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_routine_helper(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	eat_routine(t_philo *philo)
{
	if (philo->data->over)
		return ;
	pthread_mutex_lock(philo->left_fork);
	if (philo->data->over)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
	if (philo->data->number_of_philosophers == 1)
	{
		ft_usleep(philo->data->time_to_die, philo);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->over)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	eat_routine_helper(philo);
}

static void	think_sleep_routine(t_philo *philo)
{
	if (philo->data->over)
		return ;
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	if (philo->data->over)
		return ;
	print_status(philo, "is thinking");
}

int	ft_usleep(long long time, t_philo *philo)
{
	long long	now;

	now = current_time();
	while (!philo->data->over && (current_time() - now) < time)
		usleep(150);
	return (1);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->ready)
		usleep(100);
	if (philo->id & 1)
		ft_usleep(50, philo);
	while (!philo->data->over)
	{
		if (!philo->data->over)
			eat_routine(philo);
		if (!philo->data->over)
			think_sleep_routine(philo);
	}
	return (NULL);
}
