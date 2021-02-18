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

#include <pthread.h>

pthread_mutex_t	g_mutex;

/*
**	pnum	-> number of philosophers
**	ttd		-> time to die
**	tte		-> time to eat
**	tts		-> time to sleep
**	notepme	-> number of times each philosopher must eat
*/

typedef struct		s_data
{
	int				pnum;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	long			pstime;
	int				is_end;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct		s_philo
{
	int				id;
	int				lfork;
	int				rfork;
	pthread_mutex_t	*print;
	t_data			data;
	long			etime;
	int				ecount;
}					t_philo;

int					ph_strlen(const char *str);
void				print_line(char *str, int nextline);
int					ph_atoi(const char *str);
char 				*ph_itoa(long n);
long				get_time();
void				create_philos(t_data data, pthread_mutex_t *print);
void				action_print(t_philo *philo, int action);
void				*philo_life(t_philo *philo);
void				create_forks(t_data data, pthread_mutex_t *forks);
void				ph_take_forks(t_philo *philo);
void				ph_eat(t_philo *philo);
void				ph_sleep(t_philo *philo);
void				ph_think(t_philo *philo);
void				ph_usleep(long sleep_time);

void				monitoring(t_philo pdata[]);

#endif
