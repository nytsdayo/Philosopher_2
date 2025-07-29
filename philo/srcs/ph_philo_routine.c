/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:45:19 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 19:34:43 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"
#include "ph_action.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static int	ph_philo_action(t_philo *philo);

void	*ph_philo_routine(void *arg)
{
	t_philo			*philo;
	t_philo_info	*philo_info;

	philo = (t_philo *)arg;
	philo_info = philo->philo_info;
	pthread_mutex_lock(philo->table_info->start_time->mutex);
	pthread_mutex_unlock(philo->table_info->start_time->mutex);
	if (philo_info->id % 2 == 0)
	{
		ph_usleep(10);
	}
	while (true)
	{
		if (ph_philo_action(philo) != PHILO_ALIVE)
			break ;
	}
	return (NULL);
}

int	ph_philo_action(t_philo *philo)
{	
	ph_philo_act_eat(philo);
	philo->philo_info->last_eat_time = ph_get_now_time_msec() - philo->table_info->start_time->time;
	ph_print_action(philo, PHILO_SLEEP);
	ph_usleep(philo->philo_info->data->time_to_sleep);
	ph_print_action(philo, PHILO_THINK);
	return (PHILO_ALIVE);
}


// void	ph_wait_for_start(t_philo_info *philo_info)
// {
// 	while (true)
// 	{
// 		pthread_mutex_lock(philo_info->start_flag->mutex);
// 		if (philo_info->start_flag->is_started)
// 		{
// 			pthread_mutex_unlock(philo_info->start_flag->mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(philo_info->start_flag->mutex);
// 	}
// }

// int		philo_eat(t_philo *philo)
// {
// 	return (ALLIVE);
// }