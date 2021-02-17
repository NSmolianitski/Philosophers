#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
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
	philo->etime = get_time();
	action_print(philo, 2);
	usleep(philo->data.tte);
	pthread_mutex_unlock(&philo->data.forks[philo->rfork]);
	pthread_mutex_unlock(&philo->data.forks[philo->rfork]);
}

void	ph_sleep(t_philo *philo)
{
	action_print(philo, 3);
	usleep(philo->data.tts);
}

long	get_time()
{
	struct timeval	time_struct;
	long			time;

	gettimeofday(&time_struct, NULL);
	time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
	return (time);
}

void	action_print(t_philo *philo, int action)
{
	long	time;

	pthread_mutex_lock(philo->print);
	time = get_time() - philo->data.pstime;
	printf("%ld ms: Philosopher №%d", time, philo->id);
	if (action == 1)
		printf(" has taken a fork\n");
	else if (action == 2)
		printf(" is eating\n");
	else if (action == 3)
		printf(" is sleeping\n");
	else if (action == 4)
		printf(" is thinking\n");
	else if (action == 5)
		printf(" died\n");
	pthread_mutex_unlock(philo->print);
}