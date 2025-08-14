/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_act_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:51:44 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/15 03:45:08 by rnakatan         ###   ########.fr       */
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
static void	ph_add_eat_count(t_philo_eat_count *eat_count);

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
	pthread_mutex_unlock(&philo->table_info->status.mutex);
	ph_take_forks(philo);
	if (ph_isdead(philo) == true)
		return (PHILO_DEAD);
	if (ph_isexit(philo) == true)
		return (PHILO_EXIT);
	pthread_mutex_lock(&philo->table_info->start_time->mutex);
	philo->philo_info->last_eat_time = ph_get_now_time_msec()
		- philo->table_info->start_time->time;
	pthread_mutex_unlock(&philo->table_info->start_time->mutex);
	ph_print_action(philo, PHILO_EAT);
	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_eat);
	ph_release_forks(philo);
	if (ret != PHILO_ALIVE)
		return (ret);
	ph_add_eat_count(&philo->philo_info->eat_count);
	if (ph_philo_is_full(philo->philo_info) == true)
		return (PHILO_FULL);
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
		if (ph_isexit(philo) || ph_isdead(philo))
		{
			pthread_mutex_unlock(&philo->philo_info->right_fork->mutex);
			return ;
		}
		pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
		if (ph_isexit(philo) || ph_isdead(philo))
			ph_release_forks(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
		if (ph_isexit(philo) || ph_isdead(philo))
		{
			pthread_mutex_unlock(&philo->philo_info->left_fork->mutex);
			return ;
		}
		pthread_mutex_lock(&philo->philo_info->right_fork->mutex);
		ph_safe_print(philo, PHILO_TAKE_FORK);
		if (ph_isexit(philo) || ph_isdead(philo))
			ph_release_forks(philo);
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

static void	ph_add_eat_count(t_philo_eat_count *eat_count)
{
	pthread_mutex_lock(&eat_count->mutex);
	eat_count->value++;
	pthread_mutex_unlock(&eat_count->mutex);
}
