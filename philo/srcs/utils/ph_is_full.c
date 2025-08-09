#include "ph_dining.h"
#include <stdbool.h>

bool	ph_philo_is_full(t_philo_info *philo_info)
{
	if (philo_info->philo_data.max_eat_count < 0)
		return (false);
	if (philo_info->eat_count >= philo_info->philo_data.max_eat_count)
		return (true);
	return (false);
}
