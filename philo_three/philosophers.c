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
#include <stdlib.h>
#include <stdio.h>
#include "philo_three.h"

void	fill_philosopher_data(t_data *data, t_philo *philo, int i)
{
	philo->data = data;
	philo->etime = data->pstime;
	philo->id = i + 1;
	philo->ecount = 0;
	philo->eat_perm = 0;
	philo->is_hungry = 1;
}

void	death_checker(t_philo *philo)
{
	long	time;
	int		counter;

//	sem_wait(philo->data->block);
//	sem_post(philo->data->block);
//	ph_usleep(50);
	counter = 0;
	while (1)
	{
		if (philo->ecount >= philo->data->notepme)
			++counter;
		else
			counter = 0;
//		sem_wait(philo->data->block);
		time = get_time();
//		sem_wait(philo->data->death);
		if ((time - philo->etime) > philo->data->ttd)
		{
			ph_die(philo);
			sem_wait(philo->data->print);
//			sem_post(philo->data->block);
			philo->data->is_end = 1;
//			sem_post(philo->data->print);
			return ;
		}
		sem_post(philo->data->death);
//		sem_post(philo->data->block);
		if (philo->data->notepme != -1 && counter >= philo->data->pnum)
		{
			sem_wait(philo->data->block);
			philo->data->is_end = 1;
			return ;
		}
	}
}

void	*philo_life(t_philo *philo)
{
	while (1)
	{
		if (philo->data->is_end)
			exit(0);
//		while (!philo->eat_perm)
//			;
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

int		*create_philos(t_data *data, t_philo *philos_data)
{
	int			i;
	pthread_t	death;
	pthread_t	waiter;
	pid_t		*philos_pids;

	i = 0;
	philos_pids = malloc(sizeof(int) * data->pnum);
	data->pstime = get_time();
	while (i < data->pnum)
	{
		fill_philosopher_data(data, &philos_data[i], i);
		philos_pids[i] = fork();
		if (!philos_pids[i])
		{
			pthread_create(&death, NULL, (void *)death_checker, &philos_data[i]);
//			pthread_create(&waiter, NULL, (void *)waiter_cycle, &philos_data);
			philo_life(&philos_data[i]);
		}
		++i;
	}
	return (philos_pids);
}
