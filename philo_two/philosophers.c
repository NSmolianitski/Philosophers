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

void	fill_philosopher_data(t_data *data, t_philo *philo, int i)
{
	philo->data = data;
	philo->etime = 0;
	philo->id = i + 1;
	philo->ecount = 0;
	philo->eat_perm = 0;
	philo->is_hungry = 1;
}

void	death_checker(t_philo *philo)
{
	int		i;
	long	time;
	int		counter;

	sem_wait(philo[0].data->block);
	sem_post(philo[0].data->block);
	counter = 0;
	while (1)
	{
		i = 0;
		while (i < philo[0].data->pnum)
		{
			if (philo[i].ecount >= philo[i].data->notepme)
				++counter;
			else
				counter = 0;
			time = get_time();
			sem_wait(philo[0].data->block);
			if ((time - philo[i].etime) > philo[0].data->ttd)
			{
				ph_die(&philo[i]);
				philo[0].data->is_end = 1;
				return ;
			}
			sem_post(philo[0].data->block);
			++i;
		}
		if (philo->data->notepme != -1 && counter >= philo->data->pnum)
		{
			sem_wait(philo[0].data->block);
			philo[0].data->is_end = 1;
			return ;
		}
	}
}

void	*philo_life(t_philo *philo)
{
	sem_wait(philo->data->block);
	philo->etime = philo->data->pstime;
	sem_post(philo->data->block);
	while (1)
	{
		while (!philo->eat_perm)
			;
		while (1)
		{
			sem_wait(philo->data->block);
			if (philo->data->forks_num < 2)
			{
				sem_post(philo->data->block);
				continue;
			}
			else
				break ;
		}
		ph_take_forks(philo);
		sem_post(philo->data->block);
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
}

void	waiter_cycle(t_philo *philos_data)
{
	int		i;
	int		queue[philos_data[0].data->pnum];

	init_queue(queue, philos_data[0].data->pnum);
	philos_data[0].data->pstime = get_time();
	sem_post(philos_data[0].data->block);
	while (1)
	{
		i = 0;
		while (i < philos_data[0].data->pnum)
		{
			if (philos_data[0].data->is_end)
				return ;
			if (philos_data[0].is_hungry)
				add_to_queue(i, queue, philos_data[0].data->pnum);
			else
				remove_from_queue(i, queue, philos_data[0].data->pnum);
			++i;
		}
		philos_data[queue[0]].eat_perm = 1;
		while (philos_data[queue[0]].eat_perm)
			;
		move_queue(queue, philos_data[0].data->pnum);
	}
}

void	create_philos(t_data *data, t_philo *philos_data,
			pthread_t *philos_threads)
{
	int			i;
	pthread_t	waiter;

	i = 0;
	sem_wait(data->block);
	while (i < data->pnum)
	{
		fill_philosopher_data(data, &philos_data[i], i);
		pthread_create(&philos_threads[i], NULL, (void *)philo_life,
					&philos_data[i]);
		++i;
	}
	pthread_create(&waiter, NULL, (void *)waiter_cycle, philos_data);
}
