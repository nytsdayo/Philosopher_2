/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:07:27 by nyts              #+#    #+#             */
/*   Updated: 2025/08/08 15:35:36 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <unistd.h>

void	*ph_monitor_routine(void *arg)
{
	t_dining	*dining;
	t_philo		*philo;
	int			i;
	bool		is_alive;

	dining = (t_dining *)arg;
	while (true)
	{
		i = 0;
		while (i < dining->data.philo_num)
		{
			philo = dining->philos[i];
			pthread_mutex_lock(&philo->philo_info->is_alive->mutex);
			is_alive = philo->philo_info->is_alive->value;
			pthread_mutex_unlock(&philo->philo_info->is_alive->mutex);
			if (!is_alive)
			{
					pthread_mutex_lock(&dining->table_info->status.mutex);
					dining->table_info->status.is_running = false;
					pthread_mutex_unlock(&dining->table_info->status.mutex);
					return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
