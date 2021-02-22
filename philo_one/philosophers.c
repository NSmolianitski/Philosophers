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

void	*philo_life(t_philo *philo)
{
	while (1)
	{
			ph_take_forks(philo);
			ph_eat(philo);
			ph_sleep(philo);
			ph_think(philo);
	}
	return (0);
}

void	death_checker(t_philo philos_data[])
{
	long	current_time;
	int		i;

	while (1)
	{
		usleep(1000);
		i = 0;
		if (philos_data[0].data.is_end == 1)
			return ;
		current_time = get_time();
		while (i < philos_data->data.pnum)
		{
			pthread_mutex_lock(philos_data[i].print);
			if ((current_time - philos_data[i].etime) > philos_data[i].data.ttd)
			{
				print_philo_death(&philos_data[i]);
				philos_data[0].data.is_end = 1;
				return ;
			}
			pthread_mutex_unlock(philos_data[i].print);
			++i;
		}
	}
}

void	put_philos_to_table(t_data data, pthread_mutex_t *print,
				t_philo philos_data[], pthread_t philos_arr[])
{
	int		i;

	i = 0;
	while (i < data.pnum)
	{
		fill_philosopher_data(data, print, &philos_data[i], i);
		pthread_create(&philos_arr[i], NULL, (void *)philo_life,
					&philos_data[i]);
		ph_usleep(20);
		++i;
	}
}

void	create_philos(t_data data, pthread_mutex_t *print)
{
	int				i;
	t_philo			philos_data[data.pnum];
	pthread_t		philos_arr[data.pnum];
	pthread_mutex_t	forks[data.pnum];

	i = 0;
	while (i < data.pnum)
	{
		create_forks(data, &forks[i]);
		++i;
	}
	data.forks = forks;
	put_philos_to_table(data, print, philos_data, philos_arr);
	death_checker(philos_data);
	remove_philo_and_forks(data, philos_arr);
}
