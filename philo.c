/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachabi- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:42:50 by nachabi-          #+#    #+#             */
/*   Updated: 2025/07/14 01:43:49 by nachabi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	run_simulation(
		char **av, int ac, t_data *data, t_monitor_args *args)
{
	t_philo		*philos;
	pthread_t	monitor;

	if (!ft_parse_args(ac, av, data))
		return (ft_print_error("bad arguments!"));
	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos || !init_philosophers(data, philos))
		return (ft_print_error("philosophers initialization failed!"));
	if (!start_simulation(data, philos))
		return (ft_print_error("simulation failed!"));
	args->data = data;
	args->philo = philos;
	if (pthread_create(&monitor, NULL, monitor_thread, (void *)args))
		return (ft_print_error("creating monitor thread failed"));
	if (!destroy_mutexes(data, philos, &monitor))
		return (ft_print_error("joining failed!"));
	free(args);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_monitor_args	*args;

	args = malloc(sizeof(t_monitor_args));
	if (!args)
		return (ft_print_error("malloc failed!"));
	if (ac == 5 || ac == 6)
		return (run_simulation(av, ac, &data, args));
	return (ft_print_error("bad number of args!"));
}
