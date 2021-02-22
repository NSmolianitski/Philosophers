/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:40:32 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/16 14:40:33 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_two.h"

long	get_time(void)
{
	struct timeval	time_struct;
	long			time;

	gettimeofday(&time_struct, NULL);
	time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
	return (time);
}

void	ph_usleep(long sleep_time)
{
	usleep(sleep_time * 1000);
}

void	stop_threads(t_data data, pthread_t *philos_threads)
{
	int		i;

	i = 0;
	while (i < data.pnum)
	{
		pthread_detach(philos_threads[i]);
		++i;
	}
}

void	print_action(t_philo philo, int num)
{
	long	time;

	sem_wait(philo.data->print);
	time = get_time() - philo.data->pstime;
	if (num == 1)
		printf("%ld Philosopher №%d has taken a fork\n", time, philo.id);
	else if (num == 2)
		printf("%ld Philosopher №%d is eating\n", time, philo.id);
	else if (num == 3)
		printf("%ld Philosopher №%d is sleeping\n", time, philo.id);
	else if (num == 4)
		printf("%ld Philosopher №%d is thinking\n", time, philo.id);
	else if (num == 5)
		printf("%ld Philosopher №%d died\n", time, philo.id);
	sem_post(philo.data->print);
}