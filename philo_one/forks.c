/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:17:05 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/18 17:17:07 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
