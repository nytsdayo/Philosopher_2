/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:08:38 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/14 03:04:29 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdio.h>

/*
** Prints a philosopher's action to standard output in a thread-safe manner.
** This function's only job is to serialize output.
** The caller must check if the simulation is still running before calling it.
*/
void	ph_print_action(t_philo *philo, const char *action)
{
	long	now_time;
	long	start_time;

	pthread_mutex_lock(&philo->table_info->start_time->mutex);
	start_time = philo->table_info->start_time->time;
	pthread_mutex_unlock(&philo->table_info->start_time->mutex);
	pthread_mutex_lock(&philo->philo_info->print_mutex->mutex);
	now_time = ph_get_now_time_msec();
	printf("%ld %d %s\n", now_time - start_time,
		philo->philo_info->id, action);
	pthread_mutex_unlock(&philo->philo_info->print_mutex->mutex);
}
