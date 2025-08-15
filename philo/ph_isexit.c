/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_isexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:54:15 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/14 22:57:56 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdbool.h>

bool	ph_isexit(t_philo *philo)
{
	bool	is_running;

	pthread_mutex_lock(&philo->table_info->status.mutex);
	is_running = philo->table_info->status.is_running;
	pthread_mutex_unlock(&philo->table_info->status.mutex);
	return (!is_running);
}
