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
#include "philo_one.h"

void	fill_philosopher_data(t_data *data, t_philo *philo, int i)
{
	philo->data = data;
	philo->etime = data->pstime;
	philo->id = i + 1;
	philo->rfork = i - 1;
	if (!i)
		philo->rfork = data->pnum - 1;
	philo->lfork = i;
	philo->ecount = 0;
	philo->eat_perm = 0;
	philo->is_hungry = 1;
	philo->is_eating = 0;
}

void	*philo_life(t_philo *philo)
{
	while (!philo->data->ready)
		;
	philo->etime = philo->data->pstime;
	while (1)
	{
		while (!philo->eat_perm)
			;
		ph_take_forks(philo);
		pthread_mutex_unlock(&philo->data->block);
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
	philos_data[0].data->ready = 1;
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
		prepare_queue(philos_data, queue);
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
	pthread_mutex_lock(&data->block);
	while (i < data->pnum)
	{
		fill_philosopher_data(data, &philos_data[i], i);
		pthread_create(&philos_threads[i], NULL, (void *)philo_life,
					&philos_data[i]);
		++i;
	}
	pthread_create(&waiter, NULL, (void *)waiter_cycle, philos_data);
	pthread_mutex_unlock(&data->block);
}
