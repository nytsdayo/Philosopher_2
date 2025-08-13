/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:45:19 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static int	ph_philo_action(t_philo *philo);

/*
** The main routine for each philosopher thread.
** It waits at a "gate" mutex until the main thread sets the start time,
** then enters an infinite loop of actions (eat, sleep, think) until the
** simulation ends.
*/
void	*ph_philo_routine(void *arg)
{
	t_philo			*philo;
	t_philo_info	*philo_info;
	int				ret;

	philo = (t_philo *)arg;
	philo_info = philo->philo_info;
	ret = 0;
	pthread_mutex_lock(&philo->table_info->start_time->mutex);
	pthread_mutex_unlock(&philo->table_info->start_time->mutex);
	if (philo_info->id % 2 == 0)
		ph_usleep(10);
	while (true)
	{
		if (ph_philo_is_full(philo->philo_info))
		{
			ret = PHILO_FULL;
			break ;
		}
		ret = ph_philo_action(philo);
		if (ret != PHILO_ALIVE)
			break ;
	}
	(void)ret;
	return (NULL);
}

/*
** A helper function that sequences the main philosopher actions:
** eating, sleeping, and thinking.
*/
static int	ph_philo_action(t_philo *philo)
{
	int	ret;

	ret = ph_philo_act_eat(philo);
	if (ret != PHILO_ALIVE)
	{
		return (ret);
	}
	if (!ph_safe_print(philo, PHILO_SLEEP))
	{
		return (PHILO_EXIT);
	}
	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_sleep);
	if (ret != PHILO_ALIVE)
	{
		return (ret);
	}
	if (!ph_safe_print(philo, PHILO_THINK))
	{
		return (PHILO_EXIT);
	}
	return (PHILO_ALIVE);
}
