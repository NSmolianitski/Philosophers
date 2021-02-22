/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:14:12 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/18 17:14:13 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <semaphore.h>
#include "philo_two.h"
#include <stdlib.h>

void	fill_philosopher_data(t_data *data, t_philo *philo, int i)
{
	philo->data = data;
	philo->id = i + 1;
	philo->etime = get_time();
	philo->ecount = 0;
}

void	death_checker(t_philo philo[])
{
	int	i;
	long time;

	while (1)
	{
		i = 0;
		while (i < philo[0].data->pnum)
		{
			time = get_time();
			if ((time - philo[i].etime) > philo[0].data->ttd)
			{
				ph_die(&philo[i]);
				return ;
			}
			++i;
		}
	}
}

void	*philo_life(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->data->block);
		ph_take_forks(philo);
		sem_post(philo->data->block);
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
}

void	create_philos(t_data *data, t_philo *philos_data, pthread_t *philos_threads)
{
	int		i;

	i = 0;
	while (i < data->pnum)
	{
		fill_philosopher_data(data, &philos_data[i], i);
		philos_threads[i] = malloc(sizeof(pthread_t));
		pthread_create(&philos_threads[i], NULL, (void *)philo_life, &philos_data[i]);
		++i;
	}
}