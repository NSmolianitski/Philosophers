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

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>

/*
**	pnum		-> number of philosophers
**	ttd			-> time to die
**	tte			-> time to eat
**	tts			-> time to sleep
**	notepme		-> number of times each philosopher must eat
**	pstime		-> program start time
**	is_end		-> flag for ending program
**	forks		-> forks array
**	block		-> mutex for blocking threads
**	print		-> mutex for blocking stdout
**	forks_num	-> available forks number
**	ready		-> program start flag
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
	pthread_mutex_t	block;
	pthread_mutex_t	print;
	int				forks_num;
	int				ready;
}					t_data;

typedef struct		s_philo
{
	int				id;
	int				rfork;
	int				lfork;
	t_data			*data;
	long			etime;
	int				ecount;
	int				eat_perm;
	int				is_hungry;
	int				is_eating;
}					t_philo;

int					ph_atoi(const char *str);
long				get_time();
void				death_checker(t_philo *philo);
void				print_action(t_philo philo, int num);
void				fill_philosopher_data(t_data *data, t_philo *philo, int i);
void				ph_usleep(long sleep_time);
void				ph_take_forks(t_philo *philo);
void				ph_eat(t_philo *philo);
void				ph_sleep(t_philo *philo);
void				ph_think(t_philo *philo);
void				ph_die(t_philo *philo);
void				create_philos(t_data *data, t_philo *philos_data,
							pthread_t *philos_threads);
void				stop_threads(t_data data, pthread_t *philos_threads);
void				add_to_queue(int id, int queue[], int pnum);
void				remove_from_queue(int id, int queue[], int pnum);
void				move_queue(int queue[], int pnum);
void				init_queue(int *queue, int pnum);
void				prepare_queue(t_philo *philos_data, int *queue);

#endif
