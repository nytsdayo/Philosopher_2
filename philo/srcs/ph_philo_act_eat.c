/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_act_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:51:44 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 14:25:44 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"
#include "ph_action.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static void	ph_take_forks(t_philo *philo);
static void	ph_release_forks(t_philo *philo);

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
	philo->philo_info->last_eat_time
		= ph_get_now_time_msec() - philo->table_info->start_time->time;
	pthread_mutex_unlock(&philo->philo_info->last_eat_time_mutex);
	pthread_mutex_unlock(&philo->table_info->status.mutex);

	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_eat);

	ph_release_forks(philo);

	if (ret != PHILO_ALIVE)
		return (ret);
	philo->philo_info->eat_count++;
	return (PHILO_ALIVE);
}

static void	ph_take_forks(t_philo *philo)
{
	if (philo->philo_info->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->philo_info->right_fork->mutex);
		ph_safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
		ph_safe_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
		ph_safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->philo_info->right_fork->mutex);
		ph_safe_print(philo, "has taken a fork");
	}
}

static void	ph_release_forks(t_philo *philo)
{
	// The order of unlocking does not matter for correctness,
	// but unlocking in the reverse order of locking is conventional.
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

