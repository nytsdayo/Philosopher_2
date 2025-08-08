/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:45:19 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 12:56:38 by nyts             ###   ########.fr       */
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
	int				ret;

	philo = (t_philo *)arg;
	philo_info = philo->philo_info;
	pthread_mutex_lock(&philo->table_info->start_time->mutex);
	pthread_mutex_unlock(&philo->table_info->start_time->mutex);
	if (philo_info->id % 2 == 0)
		ph_usleep(10);
	while (true)
	{
		ret = ph_philo_action(philo);
		if (ret != PHILO_ALIVE)
			break ;
	}
	if (ret == PHILO_DEAD)
	{
		ph_print_action(philo, PHILO_DEATH);
		philo_info->is_alive = false;
	}
	return (NULL);
}

int	ph_philo_action(t_philo *philo)
{
	int	ret;

	ret = ph_philo_act_eat(philo);
	if (ret != PHILO_ALIVE)
		return (ret);
	philo->philo_info->last_eat_time
		= ph_get_now_time_msec() - philo->table_info->start_time->time;
	ph_print_action(philo, PHILO_SLEEP);
	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_sleep);
	if (ret != PHILO_ALIVE)
		return (ret);
	ph_print_action(philo, PHILO_THINK);
	return (PHILO_ALIVE);
}
