/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:40:40 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/16 14:40:41 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_PHILO_ONE_H
# define PHILO_ONE_PHILO_ONE_H

/*
**	pnum	-> number of philosophers
**	ttd		-> time to die
**	tte		-> time to eat
**	tts		-> time to sleep
**	notepme	-> number of times each philosopher must eat
*/

typedef struct	s_data
{
	int			pnum;
	int			ttd;
	int			tte;
	int			tts;
	int			notepme;
}				t_data;

int				ph_strlen(const char *str);
void			print_line(char *str);
int				ph_atoi(const char *str);

#endif
