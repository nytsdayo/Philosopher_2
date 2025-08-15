/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_take_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:20:35 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:23:15 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_status.h"
#include "ph_action.h"
#include "ph_utils.h"

static void	ph_take_forks_odd(t_philo *philo);
static void	ph_take_forks_even(t_philo *philo);

/*
** Implements a deadlock avoidance strategy by having even and odd numbered
** philosophers pick up their forks in a different order.
*/
void	ph_take_forks(t_philo *philo)
{
	if (philo->philo_info->id % 2 == 0)
		ph_take_forks_odd(philo);
	else
		ph_take_forks_even(philo);
}

static void	ph_take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->right_fork->mutex);
	if (ph_isexit(philo) || ph_isdead(philo))
	{
		pthread_mutex_unlock(&philo->philo_info->right_fork->mutex);
		return ;
	}
	ph_safe_print(philo, PHILO_TAKE_FORK);
	pthread_mutex_lock(&philo->philo_info->left_fork->mutex);
	if (ph_isexit(philo) || ph_isdead(philo))
		ph_release_forks(philo->philo_info);
	ph_safe_print(philo, PHILO_TAKE_FORK);
}

static void	ph_take_forks_even(t_philo *philo)
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
		ph_release_forks(philo->philo_info);
}
