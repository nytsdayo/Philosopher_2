/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_act_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

static bool	ph_isexit(t_philo *philo);

/*
** A custom usleep function that sleeps for a specified duration ('time')
** while periodically checking if the philosopher has died or if the
** simulation has ended. This makes actions like eating and sleeping
** interruptible.
*/
int	ph_act_usleep(t_philo *philo, long time)
{
	long	start_time;
	long	current_time;

	start_time = ph_get_now_time_msec();
	current_time = start_time;
	while (current_time - start_time < time)
	{
		if (ph_isdead(philo))
		{
			return (PHILO_DEAD);
		}
		if (ph_isexit(philo))
		{
			return (PHILO_EXIT);
		}
		usleep(100);
		current_time = ph_get_now_time_msec();
	}
	return (PHILO_ALIVE);
}

/*
** A thread-safe function to check if the simulation is still running.
*/
static bool	ph_isexit(t_philo *philo)
{
	bool	is_running;

	pthread_mutex_lock(&philo->table_info->status.mutex);
	is_running = philo->table_info->status.is_running;
	pthread_mutex_unlock(&philo->table_info->status.mutex);
	return (!is_running);
}
