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
#include "philo_three.h"

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
	long	sleep_start;

	sleep_start = get_time();
	while ((get_time() - sleep_start) < sleep_time)
	{
		usleep(100);
	}
}

void	restart_philo(t_data *data, int i)
{
	pthread_t	death;
	t_philo		philo;
	long		time;
	long		time2;

	time = get_time();
	sem_wait(data->death);
	++data->counter;
	sem_post(data->death);
	data->pids[i] = fork();
	fill_philosopher_data(data, &philo, i);
	philo.etime = get_time();
	philo.eat_perm = 0;
	philo.ecount = data->notepme + 1;
	time2 = get_time();
	ph_usleep(data->tte - (time2 - time));
	if (!data->pids[i])
	{
		pthread_create(&death, NULL, (void *)death_checker, &philo);
		philo_life(&philo);
	}
}

void	print_action(t_philo philo, int num)
{
	long	time;

	if (!philo.data->is_end)
	{
		sem_wait(philo.data->print);
		time = get_time() - philo.data->pstime;
		if (!philo.data->is_end || num == 5)
		{
			if (num == 1)
				printf("%ld Philosopher №%d has taken a fork\n",
								time, philo.id);
			else if (num == 2)
				printf("%ld Philosopher №%d is eating\n", time, philo.id);
			else if (num == 3)
				printf("%ld Philosopher №%d is sleeping\n", time, philo.id);
			else if (num == 4)
				printf("%ld Philosopher №%d is thinking\n", time, philo.id);
			else if (num == 5)
				printf("%ld Philosopher №%d died\n", time, philo.id);
		}
		sem_post(philo.data->print);
	}
}
