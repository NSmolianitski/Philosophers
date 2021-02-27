/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:16:10 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/18 17:16:12 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ph_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->rfork]);
	--philo->data->forks_num;
	print_action(*philo, 1);
	pthread_mutex_lock(&philo->data->forks[philo->lfork]);
	--philo->data->forks_num;
	print_action(*philo, 1);
}

void	ph_eat(t_philo *philo)
{
	philo->eat_perm = 0;
	philo->is_eating = 1;
	print_action(*philo, 2);
	++philo->ecount;
	philo->etime = get_time();
	ph_usleep(philo->data->tte);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
	++philo->data->forks_num;
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	++philo->data->forks_num;
}

void	ph_sleep(t_philo *philo)
{
	print_action(*philo, 3);
	ph_usleep(philo->data->tts);
}

void	ph_think(t_philo *philo)
{
	print_action(*philo, 4);
}

void	ph_die(t_philo *philo)
{
	print_action(*philo, 5);
}
