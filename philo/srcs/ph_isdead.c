/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_isdead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/14 23:05:09 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

/*
** Checks if a philosopher has died from starvation.
** It compares the time since the last meal with the time_to_die.
** This function is thread-safe.
*/
bool	ph_isdead(t_philo *philo)
{
	long	current_time;
	long	last_eat_time;

	last_eat_time = philo->philo_info->last_eat_time;
	current_time = ph_get_now_time_msec() - philo->table_info->start_time->time;
	if (current_time - last_eat_time
		> philo->philo_info->philo_data.time_to_die)
	{
		pthread_mutex_lock(&philo->philo_info->state.mutex);
		philo->philo_info->state.value = false;
		pthread_mutex_unlock(&philo->philo_info->state.mutex);
		return (true);
	}
	return (false);
}
