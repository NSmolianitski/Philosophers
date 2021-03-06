/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:40:52 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/16 14:40:54 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo_one.h"

/*
**	Checks arguments number and fills data struct
*/

static int		get_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	data->pnum = ph_atoi(argv[1]);
	data->ttd = ph_atoi(argv[2]);
	data->tte = ph_atoi(argv[3]);
	data->tts = ph_atoi(argv[4]);
	data->is_end = 0;
	data->ready = 0;
	if (argc == 6)
		data->notepme = ph_atoi(argv[5]);
	else
		data->notepme = -1;
	if (data->pnum <= 0 || data->ttd <= 0 || data->tte <= 0 ||
			data->tts <= 0 || (data->notepme <= 0 && argc == 6))
	{
		printf("Wrong arguments format!\n");
		return (1);
	}
	return (0);
}

static void		philosophers_cycle(t_philo *philo_data)
{
	death_checker(philo_data);
}

static void		create_forks(t_data *data)
{
	int		i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->pnum);
	i = 0;
	while (i < data->pnum)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		++i;
	}
}

int				main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*philos_threads;
	t_philo			*philos_data;

	if (get_args(argc, argv, &data))
		return (1);
	create_forks(&data);
	data.forks_num = data.pnum;
	philos_threads = malloc(sizeof(pthread_t) * data.pnum);
	philos_data = malloc(sizeof(t_philo) * data.pnum);
	pthread_mutex_init(&data.print, NULL);
	pthread_mutex_init(&data.block, NULL);
	create_philos(&data, philos_data, philos_threads);
	philosophers_cycle(philos_data);
	stop_threads(data, philos_threads);
	return (0);
}
