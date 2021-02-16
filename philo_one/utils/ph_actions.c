#include <sys/time.h>
#include "philo_one.h"

long	get_time()
{
	struct timeval	time_struct;
	long			time;

	gettimeofday(&time_struct, NULL);
	time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
	return (time);
}

void	action_print(long program_start_time, int pnum, int action)
{
	long	time;

	time = get_time() - program_start_time;
	print_line(ph_itoa(time), 0);
	print_line("ms:", 0);
	print_line(" Philosopher №", 0);
	print_line(ph_itoa(pnum), 0);
	if (action == 1)
		print_line(" has taken a fork", 1);
	else if (action == 2)
		print_line(" is eating", 1);
	else if (action == 3)
		print_line(" is sleeping", 1);
	else if (action == 4)
		print_line(" is thinking", 1);
	else if (action == 5)
		print_line(" died", 1);
}