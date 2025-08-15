/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_release_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:13:43 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:15:52 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
/*
** Releases the forks in the reverse order they were picked up, to be fair
** to other philosophers.
*/
void	ph_release_forks(t_philo_info *philo_info)
{
	if (philo_info->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo_info->left_fork->mutex);
		pthread_mutex_unlock(&philo_info->right_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo_info->right_fork->mutex);
		pthread_mutex_unlock(&philo_info->left_fork->mutex);
	}
}
