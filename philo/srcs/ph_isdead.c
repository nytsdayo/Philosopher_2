#include <stdbool.h>
#include "ph_utils.h"
#include "ph_dining.h"
#include "ph_status.h"
#include <stdio.h>

bool	ph_isdead(t_philo *philo)
{
	long	current_time;

	current_time = ph_get_now_time_msec() - philo->table_info->start_time->time;
	if (current_time - philo->philo_info->last_eat_time
		> philo->philo_info->philo_data.time_to_die)
	{
		pthread_mutex_lock(&philo->philo_info->is_alive->mutex);
		philo->philo_info->is_alive->value = false;
		pthread_mutex_unlock(&philo->philo_info->is_alive->mutex);
		return (true);
	}
	return (false);
}
