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
	philo->eat_perm = 1;
	philo->is_hungry = 1;
}

void	death_checker(t_philo *philo)
{
	long	time;

	while (1)
	{
		time = get_time();
		sem_post(philo->data->block);
		sem_wait(philo->data->death);
		if ((time - philo->etime) > philo->data->ttd)
		{
			ph_die(philo);
			sem_wait(philo->data->print);
			exit(0);
		}
		sem_post(philo->data->death);
		if (philo->data->notepme != -1 && philo->ecount == philo->data->notepme)
		{
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
			exit(1);
		}
	}
}

void	*philo_life(t_philo *philo)
{
	while (1)
	{
		if (philo->eat_perm)
		{
			if (philo->data->is_end)
				exit(0);
			while (1)
			{
				sem_wait(philo->data->block);
				if (philo->data->forks_num < 2)
				{
					sem_post(philo->data->block);
					continue ;
				}
				else
					break ;
			}
			ph_take_forks(philo);
			sem_post(philo->data->block);
			ph_eat(philo);
		}
		philo->eat_perm = 1;
		ph_sleep(philo);
		ph_think(philo);
	}
}

void	philo_wait(t_data *data)
{
	int			status;
	int			i;

	i = data->pid_index;
	waitpid(data->pids[i], &status, 0);
	status = WEXITSTATUS(status);
	if (!status)
	{
		kill_philos(data->pids, data->pnum);
		exit(0);
	}
	else if (status == 1)
		restart_philo(data, i);
}

void	create_philos(t_data *data, t_philo *philos_data)
{
	int			i;
	pthread_t	death;
	pthread_t	*philos_arr;

	i = 0;
	philos_arr = malloc(sizeof(pthread_t) * data->pnum);
	data->pids = malloc(sizeof(int) * data->pnum);
	data->pstime = get_time();
	while (i < data->pnum)
	{
		fill_philosopher_data(data, &philos_data[i], i);
		data->pids[i] = fork();
		if (!data->pids[i])
		{
			pthread_create(&death, NULL, (void *)death_checker,
					&philos_data[i]);
			philo_life(&philos_data[i]);
		}
		data->pid_index = i;
		pthread_create(&philos_arr[i], NULL, (void *)philo_wait, data);
		++i;
	}
	free(philos_arr);
}
