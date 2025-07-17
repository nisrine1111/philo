/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:34:25 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 01:30:04 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].right_fork
			= philo[(i + 1) % data->number_of_philosophers].left_fork;
		if (pthread_create(
				&philo[i].life_thread, NULL, ft_philo_routine, &philo[i]))
		{
			printf("failed to create a thread for philo %d\n", i + 1);
			return (0);
		}
		i++;
	}
	data->start_time = current_time();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].thread_start = data->start_time;
		philo[i].last_meal_time = data->start_time;
		i++;
	}
	data->ready = 1;
	return (1);
}

static int	death_check(t_data *data, t_philo *philo, int *i)
{
	print_status(&philo[*i], "died!");
	data->over = 1;
	// print_d();
	printf("%d\n", philo->data->over);
	printf("ooooooooooooooooooooooooooooooooooooooooo\n");
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

static int	surviving_check(t_data *data, t_philo *philo)
{
	data->over = 1;
	printf("yessssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n");
	printf("All philos have eaten %d meals!\n", philo->data->number_of_meals);
	printf("THANK GOD, everyone is alive :)\n");
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

int	simulation_monitor(t_data *data, t_philo *philo)
{
	int	i;
	int	all_ate;

	while (!data->ready)
		usleep(100);
	while (!data->over)
	{
		i = 0;
		all_ate = 1;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (current_time() - philo[i].last_meal_time > data->time_to_die)
				return (death_check(data, philo, &i));
			if (data->meal_check != 0
				&& philo[i].meals_eaten < data->number_of_meals)
				all_ate = 0;
			if (data->meal_check != 0 && all_ate)
				return (surviving_check(data, philo));
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_monitor_args	*args;

	args = (t_monitor_args *)arg;
	if (!simulation_monitor(args->data, args->philo))
		ft_print_error("simulatin monitor failed");
	return (NULL);
}
