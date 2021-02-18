#include "philo_one.h"

void	ph_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data.forks[philo->lfork]);
		action_print(philo, 1);
		pthread_mutex_lock(&philo->data.forks[philo->rfork]);
		action_print(philo, 1);
	}
	else
	{
		pthread_mutex_lock(&philo->data.forks[philo->rfork]);
		action_print(philo, 1);
		pthread_mutex_lock(&philo->data.forks[philo->lfork]);
		action_print(philo, 1);
	}
}

void	ph_eat(t_philo *philo)
{
	action_print(philo, 2);
	philo->etime = get_time();
	++philo->ecount;
	ph_usleep(philo->data.tte);
	pthread_mutex_unlock(&philo->data.forks[philo->rfork]);
	pthread_mutex_unlock(&philo->data.forks[philo->lfork]);
}

void	ph_sleep(t_philo *philo)
{
	action_print(philo, 3);
	ph_usleep(philo->data.tts);
}


void	ph_think(t_philo *philo)
{
	action_print(philo, 4);
}