#include "ph_dining.h"
#include "ph_status.h"
#include "ph_action.h"
#include <unistd.h>
#include "ph_utils.h"

int	ph_act_usleep(t_philo *philo, long time)
{
	long	start_time;
	long	current_time;

	start_time = ph_get_now_time_msec();
	current_time = start_time;
	while (current_time - start_time < time)
	{
		if (ph_isdead(philo))
			return (PHILO_DEAD);
		usleep(100);
		current_time = ph_get_now_time_msec();
	}
	return (PHILO_ALIVE);
}
