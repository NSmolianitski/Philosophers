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
#include <signal.h>
#include "philo_three.h"

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
	while (1)
		;
}

static void		remove_sems(void)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("block");
	sem_unlink("death");
}

static void		kill_philos(pid_t *philos_pids, int pnum)
{
	int		i;

	i = 0;
	while (i < pnum)
	{
		kill(philos_pids[i], SIGTERM);
		++i;
	}
}

int				main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos_data;
	pid_t			*philos_pids;
	int				status;

	remove_sems();
	if (get_args(argc, argv, &data))
		return (1);
	data.forks = sem_open("forks", O_CREAT, 0666, data.pnum);
	data.forks_num = data.pnum;
	philos_data = malloc(sizeof(t_philo) * data.pnum);
	data.print = sem_open("print", O_CREAT, 0666, 1);
	data.block = sem_open("block", O_CREAT, 0666, 1);
	data.death = sem_open("death", O_CREAT, 0666, 1);
	philos_pids = create_philos(&data, philos_data);
	waitpid(-1, &status, 0);
	kill_philos(philos_pids, data.pnum);
	remove_sems();
	return (0);
}
