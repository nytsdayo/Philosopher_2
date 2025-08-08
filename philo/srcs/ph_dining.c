/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dining.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 08:32:05 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 12:46:15 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdlib.h>
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int	ph_run_dining(t_dining *dining);

static void	ph_handle_single_philosopher(t_dining_data dining_data)
{
	printf("0 1 has taken a fork\n");
	ph_usleep(dining_data.time_to_die);
	printf("%d 1 died\n", dining_data.time_to_die);
}

int	ph_dining(t_dining_data dining_data)
{
	t_dining	*dining;
	int			ret;

	if (dining_data.philo_num == 1)
		ph_handle_single_philosopher(dining_data);
	else
	{
		ret = ph_init_dining(&dining, dining_data);
		if (ret != PH_SUCCESS)
		{
			fprintf(stderr, "Error initializing dining: %d\n", ret);
			if (ret == PH_MEMORY_ERROR)
				fprintf(stderr, "Memory allocation error\n");
			if (dining)
				ph_free_resources(dining);
			return (ret);
		}
		ret = ph_init_philos(&dining->philos, dining);
		if (ret != PH_SUCCESS)
		{
			fprintf(stderr, "Error initializing philosophers: %d\n", ret);
			ph_free_resources(dining);
			return (ret);
		}
		ret = ph_run_dining(dining);
		if (ret != PH_SUCCESS)
			return (ret);
		ph_free_resources(dining);
	}
	return (PH_SUCCESS);
}

int				ph_run_dining(t_dining *dining)
{
	int	i;

	pthread_mutex_lock(&dining->table_info->start_time->mutex);
	i = 0;
	while (i < dining->data.philo_num)
	{
		if (pthread_create(&dining->philo_threads[i], NULL,
				ph_philo_routine, dining->philos[i]) != 0)
		{
			fprintf(stderr, "Error creating thread for philosopher %d\n", i + 1);
			return (PH_MEMORY_ERROR);
		}
		i++;
	}
	pthread_create(&dining->monitor_thread, NULL,
		ph_monitor_routine, dining);
	pthread_detach(dining->monitor_thread);
	dining->table_info->start_time->time = ph_get_now_time_msec();
	pthread_mutex_unlock(&dining->table_info->start_time->mutex);
	i = 0;
	while (i < dining->data.philo_num)
	{
		if (pthread_join(dining->philo_threads[i], NULL) != 0)
		{
			fprintf(stderr, "Error joining thread for philosopher %d\n", i + 1);
			return (PH_THREAD_ERROR);
		}
		i++;
	}
	return (PH_SUCCESS);
}

t_philo_data	ph_get_philo_data(t_dining_data data)
{
	t_philo_data	philo_data;

	philo_data.time_to_die = data.time_to_die;
	philo_data.time_to_eat = data.time_to_eat;
	philo_data.time_to_sleep = data.time_to_sleep;
	philo_data.max_eat_count = data.max_eat_count;
	return (philo_data);
}
