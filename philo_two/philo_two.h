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

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <semaphore.h>

/*
**	pnum	-> number of philosophers
**	ttd		-> time to die
**	tte		-> time to eat
**	tts		-> time to sleep
**	notepme	-> number of times each philosopher must eat
**	pstime	-> program start time
**	is_end	-> flag for ending program
**	forks	-> forks array
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
	sem_t			*forks;
	sem_t			*block;
	sem_t			*print;
	int				forks_num;
}					t_data;

typedef struct		s_philo
{
	int				id;
	t_data			*data;
	long			etime;
	int				ecount;
	int				eat_perm;
	int				is_hungry;
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

#endif
