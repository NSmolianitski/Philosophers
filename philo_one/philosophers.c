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
	int 	i;

	while (1)
	{
		i = 0;
		usleep(1000);
		current_time = get_time();
		while (i < philos_data->data.pnum)
		{
			pthread_mutex_lock(philos_data[i].print);
			if ((current_time - philos_data[i].etime) > philos_data[i].data.ttd)
			{
				action_print(&philos_data[i], 5);
				philos_data[i].data.is_end = 1;
				return ;
			}
			if (philos_data[i].data.is_end)
				return ;
			pthread_mutex_unlock(philos_data[i].print);
			++i;
		}
	}
}

void	*check_eat_times(t_philo philos_data[])
{
	int 	i;
	int		counter;
	int		notepme;

	notepme = philos_data[0].data.notepme;
	while (1)
	{
		counter = 0;
		i = 0;
		while (i < philos_data[i].data.pnum)
		{
			if (philos_data[i].data.is_end)
				return (0);
			if (notepme != -1 && philos_data[i].ecount >= notepme)
				++counter;
			if (notepme != -1 && counter == philos_data[i].data.pnum)
			{
				pthread_mutex_lock(philos_data[i].print);
				philos_data[i].data.is_end = 1;
				return (0);
			}
			++i;
		}
	}
}

void	put_philos_to_table(t_data data, pthread_mutex_t *print, t_philo philos_data[], pthread_t philos_arr[])
{
	int		i;

	i = 0;
	while (i < data.pnum)
	{
		fill_philosopher_data(data, print, &philos_data[i], i);
		pthread_create(&philos_arr[i], NULL, (void *)philo_life, &philos_data[i]);
		ph_usleep(10);
		++i;
	}
}

void	create_philos(t_data data, pthread_mutex_t *print)
{
	int				i;
	t_philo			philos_data[data.pnum];
	pthread_t		philos_arr[data.pnum];
	pthread_mutex_t	forks[data.pnum];
	pthread_t		eat_checker;

	i = 0;
	while (i < data.pnum)
	{
		create_forks(data, &forks[i]);
		++i;
	}
	data.forks = forks;
	put_philos_to_table(data, print, philos_data, philos_arr);
	pthread_create(&eat_checker, NULL, (void *)check_eat_times, philos_data);
	death_checker(philos_data);
	stop_threads(data, philos_arr);
	i = 0;
	while (i < data.pnum)
	{
		pthread_join(philos_arr[i], NULL);
		++i;
	}
	pthread_join(eat_checker, NULL);
}