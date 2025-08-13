/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_safe_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include <pthread.h>
#include <stdbool.h>

/*
** A wrapper for ph_print_action that first checks if the simulation is
** still running. This prevents printing messages after the simulation has
** officially ended. The status mutex is held during the check and the
** print to prevent race conditions.
*/
bool	ph_safe_print(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->table_info->status.mutex);
	if (philo->table_info->status.is_running)
	{
		ph_print_action(philo, action);
	}
	else
	{
		pthread_mutex_unlock(&philo->table_info->status.mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->table_info->status.mutex);
	return (true);
}
