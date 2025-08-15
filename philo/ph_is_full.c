/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_is_full.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:01:59 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:39:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdbool.h>

/*
** Checks if a philosopher is "full", meaning they have completed the
** required number of meals. If max_eat_count is not set, this always
** returns false.
*/
bool	ph_philo_is_full(t_philo_info *philo_info)
{
	int	eat_count;

	if (philo_info->philo_data.max_eat_count < 0)
		return (false);
	pthread_mutex_lock(&philo_info->eat_count.mutex);
	eat_count = philo_info->eat_count.value;
	pthread_mutex_unlock(&philo_info->eat_count.mutex);
	if (eat_count == philo_info->philo_data.max_eat_count)
		return (true);
	return (false);
}
