/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:07:27 by nyts              #+#    #+#             */
/*   Updated: 2025/08/15 02:38:29 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

static bool	ph_is_finish_dining(t_philo **philos,
				t_table_info *table_info,
				t_dining_data philo_num);

/*
** The monitor's main routine. It runs in a separate thread and continuously
** checks the status of all philosophers. It stops the simulation if a
** philosopher dies or if all philosophers have eaten enough.
*/
void	*ph_monitor_routine(void *arg)
{
	t_dining	*dining;

	dining = (t_dining *)arg;
	ph_wait_start(dining->table_info->start_time);
	while (true)
	{
		if (ph_is_finish_dining(dining->philos, dining->table_info,
				dining->data) == true)
			break ;
		usleep(100);
	}
	return (NULL);
}

static bool	ph_finish_dining(
				t_table_status *table_status_ptr,
				t_philo	*philo);

static bool	ph_is_finish_dining(t_philo **philos,
			t_table_info *table_info,
			t_dining_data dining_data)
{
	int			i;
	int			full_philos_count;
	int			ret;
	bool		should_exit;

	i = -1;
	should_exit = false;
	full_philos_count = 0;
	while (++i < dining_data.philo_num && should_exit == false)
	{
		ret = ph_get_philo_state(&philos[i]->philo_info->state);
		if (ret != PHILO_ALIVE)
		{
			if (ret == PHILO_DEAD)
				should_exit = ph_finish_dining(&table_info->status, philos[i]);
			else if (ret == PHILO_FULL)
				full_philos_count++;
		}
	}
	if (dining_data.max_eat_count >= 0
		&& full_philos_count == dining_data.philo_num)
		should_exit = ph_finish_dining(&table_info->status, NULL);
	return (should_exit);
}

static bool	ph_finish_dining(t_table_status *table_status_ptr,
		t_philo *philo)
{
	pthread_mutex_lock(&table_status_ptr->mutex);
	table_status_ptr->is_running = false;
	pthread_mutex_unlock(&table_status_ptr->mutex);
	if (philo && ph_get_philo_state(&philo->philo_info->state) == PHILO_DEAD)
		ph_print_action(philo, PHILO_DEATH);
	return (true);
}
