/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_act_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:51:44 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:23:44 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static void	ph_add_eat_count(t_philo_eat_count *eat_count);
static void	ph_set_last_eat_time(t_start_time *start_time, long *last_eat_time);

/*
** The philosopher's eating action. This function handles taking forks,
** eating for a specified time, and then releasing the forks. It is
** designed to be deadlock-free.
*/
int	ph_philo_act_eat(t_philo *philo)
{
	int	ret;

	if (ph_get_table_status(&philo->table_info->status) == false)
		return (PHILO_EXIT);
	ph_take_forks(philo);
	if (ph_isdead(philo) == true)
	{
		ph_release_forks(philo->philo_info);
		return (PHILO_DEAD);
	}
	if (ph_isexit(philo) == true)
		return (PHILO_EXIT);
	ph_set_last_eat_time(philo->table_info->start_time,
		&philo->philo_info->last_eat_time);
	ph_print_action(philo, PHILO_EAT);
	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_eat);
	ph_release_forks(philo->philo_info);
	if (ret != PHILO_ALIVE)
		return (ret);
	ph_add_eat_count(&philo->philo_info->eat_count);
	if (ph_philo_is_full(philo->philo_info) == true)
		return (PHILO_FULL);
	return (PHILO_ALIVE);
}

static void	ph_add_eat_count(t_philo_eat_count *eat_count)
{
	pthread_mutex_lock(&eat_count->mutex);
	eat_count->value++;
	pthread_mutex_unlock(&eat_count->mutex);
}

static void	ph_set_last_eat_time(t_start_time *start_time, long *last_eat_time)
{
	pthread_mutex_lock(&start_time->mutex);
	*last_eat_time = ph_get_now_time_msec() - start_time->time;
	pthread_mutex_unlock(&start_time->mutex);
}
