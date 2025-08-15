/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_safe_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:02:10 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:39:09 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
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
