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
#include "philo_one.h"

long	get_time()
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

void	action_print(t_philo *philo, int action)
{
	long	time;

	time = get_time() - philo->data.pstime;
	printf("%ld ms: Philosopher №%d", time, philo->id);
	if (action == 1)
		printf(" has taken a fork\n");
	else if (action == 2)
		printf(" is eating\n");
	else if (action == 3)
		printf(" is sleeping\n");
	else if (action == 4)
		printf(" is thinking\n");
	else if (action == 5)
		printf(" died\n");
}

void	stop_threads(t_data data, pthread_t philos_arr[])
{
	int		i;

	i = 0;
	while (i < data.pnum)
	{
		pthread_detach(philos_arr[i]);
		++i;
	}
}

void	fill_philosopher_data(t_data data, pthread_mutex_t *print, t_philo *philo, int i)
{
	philo->data = data;
	philo->print = print;
	philo->id = i + 1;
	philo->lfork = i;
	philo->etime = get_time();
	philo->ecount = 0;
	if (i)
		philo->rfork = i - 1;
	else
		philo->rfork = data.pnum - 1;
}
