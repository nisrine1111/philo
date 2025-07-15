/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 02:15:05 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 02:27:15 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > INT_MAX)
			return (0);
	}
	return (res);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	digit_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_is_digit(av[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_parse_args(char ac, char **av, t_data *data)
{
	int	mtx;

	mtx = 0;
	if (!digit_check(av))
		return (0);
	data->number_of_philosophers = (int)ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meal_check = 0;
	data->number_of_meals = -1;
	data->ready = 0;
	data->start_time = 0;
	if (ac == 6)
	{
		data->meal_check = 1;
		data->number_of_meals = (int)ft_atoi(av[5]);
	}
	data->over = 0;
	if (data->number_of_philosophers == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| data->number_of_meals == 0)
		return (0);
	mtx = init_mutexes(data);
	return (mtx);
}
