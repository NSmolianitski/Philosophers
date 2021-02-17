#include "philo_one.h"

void		monitoring(t_philo pdata[])
{
	int		i;
	long	current_time;

	while (1)
	{
		i = 0;
		current_time = get_time();
		if ((current_time - pdata[i].etime) > pdata[i].data.ttd)
			action_print(&pdata[i], 5);
	}
}