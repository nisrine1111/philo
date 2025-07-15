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
	if (!philo->data->over)
		printf("%lld ms %d %s\n",
			current_time() - philo->thread_start, philo->id, msg);
}

void	print_d(void)
{
	printf("\033[0;31m");
	printf("      _____\n");
	printf("     /     \\\n");
	printf("    | () () |\n");
	printf("    |  ___  |\n");
	printf("     \\_____/\n");
	printf("    ___|_|___\n");
	printf("   /         \\\n");
	printf("  |  RIP 💀   |\n");
	printf("  |___________|\n");
	printf("\033[0m");
}
