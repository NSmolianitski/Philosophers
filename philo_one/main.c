/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:40:52 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/16 14:40:54 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
**	Checks arguments number and fills data struct
*/

static int		get_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		print_line("Wrong number of arguments!");
		return (1);
	}
	data->pnum = ph_atoi(argv[1]);
	data->ttd = ph_atoi(argv[2]);
	data->tte = ph_atoi(argv[3]);
	data->tts = ph_atoi(argv[4]);
	if (argc == 6)
		data->notepme = ph_atoi(argv[5]);
	else
		data->notepme = -1;
	if (!data->pnum || !data->ttd || !data->tte || !data->tts || !data->notepme)
	{
		print_line("Wrong aguments format!");
		return (1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_data	data;

	if (get_args(argc, argv, &data))
		return (1);
	return (0);
}
