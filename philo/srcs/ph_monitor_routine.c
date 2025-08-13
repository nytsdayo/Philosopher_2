/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:07:27 by nyts              #+#    #+#             */
/*   Updated: 2025/08/14 04:54:54 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

static bool	ph_monitor_is_full(t_philo_info *philo_info);
static bool	ph_stop_simulation(t_dining *dining);

/*
** Checks if a single philosopher has reached their maximum eat count.
*/
static bool	ph_monitor_is_full(t_philo_info *philo_info)
{
	int		philo_eat_count;

	pthread_mutex_lock(&philo_info->eat_count.mutex);
	philo_eat_count = philo_info->eat_count.value;
	pthread_mutex_unlock(&philo_info->eat_count.mutex);
	if (philo_info->philo_data.max_eat_count < 0)
	{
		return (false);
	}
	if (philo_eat_count >= philo_info->philo_data.max_eat_count)
	{
		return (true);
	}
	return (false);
}

/*
** Sets the simulation status to not running, effectively stopping all
** philosopher threads.
*/
static bool	ph_stop_simulation(t_dining *dining)
{
	pthread_mutex_lock(&dining->table_info->status.mutex);
	dining->table_info->status.is_running = false;
	pthread_mutex_unlock(&dining->table_info->status.mutex);
	return (true);
}

/*
** The monitor's main routine. It runs in a separate thread and continuously
** checks the status of all philosophers. It stops the simulation if a
** philosopher dies or if all philosophers have eaten enough.
*/
void	*ph_monitor_routine(void *arg)
{
	t_dining	*dining;
	int			i;
	int			full_philos_count;
	bool		should_exit;

	dining = (t_dining *)arg;
	pthread_mutex_lock(&dining->table_info->start_time->mutex);
	pthread_mutex_unlock(&dining->table_info->start_time->mutex);
	should_exit = false;
	while (!should_exit)
	{
		i = -1;
		full_philos_count = 0;
		while (++i < dining->data.philo_num && !should_exit)
		{
			if (ph_isdead(dining->philos[i]))
			{
				pthread_mutex_lock(&dining->table_info->status.mutex);
				if (dining->table_info->status.is_running)
				{
					dining->table_info->status.is_running = false;
					ph_print_action(dining->philos[i], PHILO_DEATH);
				}
				pthread_mutex_unlock(&dining->table_info->status.mutex);
				should_exit = true;
			}
			else
			{
				if (ph_monitor_is_full(dining->philos[i]->philo_info))
				{
					full_philos_count++;
				}
			}
		}
		if (dining->data.max_eat_count >= 0
			&& full_philos_count == dining->data.philo_num)
		{
			should_exit = ph_stop_simulation(dining);
		}
		usleep(100);
	}
	return (NULL);
}
