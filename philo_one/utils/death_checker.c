/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:17:09 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/27 13:17:12 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		is_dead(t_philo *philo, int *counter)
{
	int		i;
	long	time;

	i = 0;
	while (i < philo[0].data->pnum)
	{
		if (philo[i].ecount >= philo[i].data->notepme)
			++(*counter);
		else
			(*counter) = 0;
		time = get_time();
		pthread_mutex_lock(&philo[0].data->block);
		if ((time - philo[i].etime) > philo[0].data->ttd)
		{
			ph_die(&philo[i]);
			philo[0].data->is_end = 1;
			return (1);
		}
		pthread_mutex_unlock(&philo[0].data->block);
		++i;
	}
	return (0);
}

void	death_checker(t_philo *philo)
{
	int		counter;

	counter = 0;
	while (!philo[0].data->ready)
		;
	ph_usleep(50);
	while (1)
	{
		if (is_dead(philo, &counter))
			return ;
		if (philo->data->notepme != -1 && counter >= philo->data->pnum)
		{
			pthread_mutex_lock(&philo[0].data->block);
			philo[0].data->is_end = 1;
			return ;
		}
	}
}
