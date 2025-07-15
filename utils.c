/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:34:56 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 01:42:02 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_error(char *msg)
{
	return (printf("ERROR:\n%s\n", msg));
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = 0;
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (0);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_philosophers(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = 0;
		philos[i].thread_start = 0;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = 0;
		philos[i].data = data;
		i++;
	}
	return (1);
}

int	destroy_mutexes(t_data *data, t_philo *philo, pthread_t *monitor)
{
	int	i;

	pthread_join(*monitor, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philo[i].life_thread, (void *)&philo[i]);
		i++;
	}
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(&data->meal_mutex);
	free(data->forks);
	free(philo);
	return (1);
}
