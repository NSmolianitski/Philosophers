#include <stdlib.h>
#include <unistd.h>
#include "philo_one.h"

void	fill_philosopher_data(t_data data, pthread_mutex_t *print, t_philo *philo, int i)
{
	philo->data = data;
	philo->print = print;
	philo->id = i + 1;
	philo->lfork = i;
	philo->etime = get_time();
	if (i)
		philo->rfork = i - 1;
	else
		philo->rfork = data.pnum - 1;
	action_print(philo, 5);
}

void	philo_life(t_philo *philo)
{
	while (1)
	{
		ph_take_forks(philo);
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
}

void	death_checker(t_data data, t_philo philos_data[])
{
	long	current_time;
	int 	i;

	while (1)
	{
		i = 0;
		current_time = get_time();
		if ((current_time - philos_data[i].etime) > philos_data[i].data.ttd)
		{
			action_print(&philos_data[i], 5);
			return ;
		}
	}
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

void	create_philos(t_data data, pthread_mutex_t *print)
{
	int				i;
	t_philo			philos_data[data.pnum];
	pthread_t		philos_arr[data.pnum];
	pthread_mutex_t	forks[data.pnum];
	pthread_t		monitor;

	i = 0;
	while (i < data.pnum)
	{
		create_forks(data, &forks[i]);
		++i;
	}
	data.forks = forks;
	i = 0;
	while (i < data.pnum)
	{
		fill_philosopher_data(data, print, &philos_data[i], i);
		pthread_create(&philos_arr[i], NULL, philo_life, &philos_data[i]);
		ph_usleep(20);
		++i;
	}
	death_checker(data, philos_data);
	stop_threads(data, philos_arr);
	i = 0;
	while (i < data.pnum)
	{
		pthread_join(philos_arr[i], NULL);
		++i;
	}
//	pthread_create(&monitor, NULL, monitoring, philos_data);
//	pthread_join(monitor, NULL);
}