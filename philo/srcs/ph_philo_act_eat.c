/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_act_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:51:44 by rnakatan          #+#    #+#             */
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
#include <unistd.h>

static void	ph_take_forks(t_philo *philo);
static void	ph_release_forks(t_philo *philo);

/*
** The philosopher's eating action. This function handles taking forks,
** eating for a specified time, and then releasing the forks. It is
** designed to be deadlock-free.
*/
int	ph_philo_act_eat(t_philo *philo)
{
	int	ret;

	ph_take_forks(philo);
	pthread_mutex_lock(&philo->table_info->status.mutex);
	if (philo->table_info->status.is_running == false)
	{
		pthread_mutex_unlock(&philo->table_info->status.mutex);
		ph_release_forks(philo);
		return (PHILO_EXIT);
	}
	ph_print_action(philo, PHILO_EAT);
	pthread_mutex_lock(&philo->philo_info->last_eat_time_mutex);
	philo->philo_info->last_eat_time = ph_get_now_time_msec()
		- philo->table_info->start_time->time;
	pthread_mutex_unlock(&philo->philo_info->last_eat_time_mutex);
	pthread_mutex_unlock(&philo->table_info->status.mutex);
	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_eat);
	ph_release_forks(philo);
	if (ret != PHILO_ALIVE)
	{
		return (ret);
	}
	philo->philo_info->eat_count++;
	return (PHILO_ALIVE);
}

/*
** Implements a deadlock avoidance strategy by having even and odd numbered
** philosophers pick up their forks in a different order.
*/
static void	ph_take_forks(t_philo *philo)
{
	if (philo->philo_info->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->philo_info->right_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
		pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
		pthread_mutex_lock(&philo->philo_info->right_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
	}
}

/*
** Releases the forks in the reverse order they were picked up, to be fair
** to other philosophers.
*/
static void	ph_release_forks(t_philo *philo)
{
	if (philo->philo_info->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->philo_info->left_fork->mutex);
		pthread_mutex_unlock(&philo->philo_info->right_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->philo_info->right_fork->mutex);
		pthread_mutex_unlock(&philo->philo_info->left_fork->mutex);
	}
}
