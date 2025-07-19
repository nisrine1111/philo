/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 02:08:49 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 02:14:15 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (!is_over(philo))
		printf("%lld %d %s\n",
			current_time() - philo->thread_start, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

int	is_over(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->over_mutex);
	if (philo->data->over)
	{
		pthread_mutex_unlock(&philo->data->over_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->over_mutex);
	return (0);
}

int	is_ready(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_mutex);
	if (philo->data->ready)
	{
		pthread_mutex_unlock(&philo->data->ready_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->ready_mutex);
	return (0);
}
