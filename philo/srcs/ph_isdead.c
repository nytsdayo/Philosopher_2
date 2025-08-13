/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_isdead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:01:26 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 20:01:27 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ph_utils.h"
#include "ph_dining.h"
#include "ph_status.h"
#include <stdio.h>

bool	ph_isdead(t_philo *philo)
{
	long	current_time;
	long	last_eat;

	pthread_mutex_lock(&philo->philo_info->last_eat_time_mutex);
	last_eat = philo->philo_info->last_eat_time;
	pthread_mutex_unlock(&philo->philo_info->last_eat_time_mutex);
	current_time = ph_get_now_time_msec() - philo->table_info->start_time->time;
	if (current_time - last_eat
		> philo->philo_info->philo_data.time_to_die)
	{
		pthread_mutex_lock(&philo->philo_info->is_alive->mutex);
		philo->philo_info->is_alive->value = false;
		pthread_mutex_unlock(&philo->philo_info->is_alive->mutex);
		return (true);
	}
	return (false);
}
