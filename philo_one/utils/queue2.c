/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:01:43 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/27 13:01:45 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		neighbors_eat_check(t_philo *philos_data, int i)
{
	int		right;
	int		left;

	right = i - 1;
	left = i + 1;
	if (right < 0)
		right = philos_data[0].data->pnum - 1;
	if (left > philos_data[0].data->pnum)
		left = philos_data[0].data->pnum - 1;
	if (philos_data[left].is_eating || philos_data[right].is_eating)
		return (1);
	return (0);
}

void	prepare_queue(t_philo *philos_data, int *queue)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < philos_data[0].data->pnum)
	{
		if (philos_data[0].data->forks_num >= 2 &&
				!neighbors_eat_check(philos_data, queue[i]))
		{
			tmp = queue[0];
			queue[0] = queue[i];
			while (i > 0)
			{
				queue[i] = queue[i - 1];
				--i;
			}
			if (queue[0] != tmp)
				queue[1] = tmp;
			return ;
		}
		++i;
	}
}
