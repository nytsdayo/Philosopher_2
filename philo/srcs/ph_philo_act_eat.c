/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_act_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:51:44 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 00:00:10 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"
#include "ph_action.h"
#include <stdio.h>
#include <unistd.h>

static int	ph_philo_eat_even(t_philo *philo);
static int	ph_philo_eat_odd(t_philo *philo);
static int	ph_philo_is_full(t_philo_info *philo_info);

int	ph_philo_act_eat(t_philo *philo)
{
	int	ret;

	while (true)
	{
		if (ph_isdead(philo))
			return (PHILO_DEAD);
		if (philo->philo_info->id % 2 == 0)
			ret = ph_philo_eat_even(philo);
		else
			ret = ph_philo_eat_odd(philo);
		if (ret == TAKEN)
			break ;
		usleep(100); // Sleep to avoid busy waiting
	}
	ph_print_action(philo, PHILO_EAT);
	ret = ph_act_usleep(philo, philo->philo_info->philo_data.time_to_eat);
	philo->philo_info->left_fork->is_used = false;
	philo->philo_info->right_fork->is_used = false;
	if (ret != PHILO_ALIVE)
		return (ret);
	philo->philo_info->eat_count++;
	philo->philo_info->last_eat_time
		= ph_get_now_time_msec() - philo->table_info->start_time->time;
	if (ph_philo_is_full(philo->philo_info))
		return (PHILO_FULL);
	return (PHILO_ALIVE);
}

static int	ph_philo_eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_info->right_fork->mutex);
	if (philo->philo_info->right_fork->is_used)
	{
		pthread_mutex_unlock(philo->philo_info->right_fork->mutex);
		return (NOT_TAKEN);
	}
	philo->philo_info->right_fork->is_used = true;
	pthread_mutex_unlock(philo->philo_info->right_fork->mutex);
	pthread_mutex_lock(philo->philo_info->left_fork->mutex);
	if (philo->philo_info->left_fork->is_used)
	{
		pthread_mutex_lock(philo->philo_info->right_fork->mutex);
		philo->philo_info->right_fork->is_used = false;
		pthread_mutex_unlock(philo->philo_info->right_fork->mutex);
		pthread_mutex_unlock(philo->philo_info->left_fork->mutex);
		return (NOT_TAKEN);
	}
	philo->philo_info->left_fork->is_used = true;
	pthread_mutex_unlock(philo->philo_info->left_fork->mutex);
	return (TAKEN);
}

static int	ph_philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_info->left_fork->mutex);
	if (philo->philo_info->left_fork->is_used)
	{
		pthread_mutex_unlock(philo->philo_info->left_fork->mutex);
		return (NOT_TAKEN);
	}
	philo->philo_info->left_fork->is_used = true;
	pthread_mutex_unlock(philo->philo_info->left_fork->mutex);
	pthread_mutex_lock(philo->philo_info->right_fork->mutex);
	if (philo->philo_info->right_fork->is_used)
	{
		pthread_mutex_lock(philo->philo_info->left_fork->mutex);
		philo->philo_info->left_fork->is_used = false;
		pthread_mutex_unlock(philo->philo_info->left_fork->mutex);
		pthread_mutex_unlock(philo->philo_info->right_fork->mutex);
		return (NOT_TAKEN);
	}
	philo->philo_info->right_fork->is_used = true;
	pthread_mutex_unlock(philo->philo_info->right_fork->mutex);
	return (TAKEN);
}

static int	ph_philo_is_full(t_philo_info *philo_info)
{
	if (philo_info->philo_data.max_eat_count <= 0)
		return (PHILO_ALIVE);
	if (philo_info->eat_count >= philo_info->philo_data.max_eat_count)
	{
		philo_info->is_alive = false;
		return (PHILO_FULL);
	}
	return (PHILO_ALIVE);
}
