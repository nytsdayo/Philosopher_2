/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_act_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:51:44 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 19:26:11 by rnakatan         ###   ########.fr       */
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

int	ph_philo_act_eat(t_philo *philo)
{
	int	ret;

	while (true)
	{
		if (philo->philo_info->id % 2 == 0)
			ret = ph_philo_eat_even(philo);
		else
			ret = ph_philo_eat_odd(philo);
		if (ret == TAKEN)
			break ;
		usleep(1);
	}
	ph_print_action(philo, PHILO_EAT);
	ph_usleep(philo->philo_info->data->time_to_eat);
	philo->philo_info->left_fork->is_used = false;
	philo->philo_info->right_fork->is_used = false;
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
