#include <pthread.h>
#include "philo_one.h"

void	create_forks(t_data data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data.pnum)
	{
		pthread_mutex_init(&forks[i], NULL);
		++i;
	}
}