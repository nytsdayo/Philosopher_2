/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:45:19 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 00:38:58 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

static void	ph_wait_for_start(t_philo *philo);

void	*ph_philo_routine(void *arg)
{
	// test routine
	t_philo	*philo;
	long	now_time;
	long	start_time;

	// wait for start signal
	philo = (t_philo *)arg;
	now_time = ph_get_now_time_msec();
	printf("%ld: Philosopher %d is sitting down.\n", now_time, philo->id);
	ph_wait_for_start(philo);
	start_time = ph_get_now_time_msec();
	now_time = ph_get_now_time_msec();
	pthread_mutex_lock(philo->print_mutex->mutex);
	printf("%ld: Philosopher %d is eating.\n", now_time - start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex->mutex);
	ph_usleep(philo->data->time_to_eat);
	now_time = ph_get_now_time_msec();
	printf("%ld: Philosopher %d is sleeping.\n", now_time - start_time, philo->id);
	ph_usleep(philo->data->time_to_sleep);
	now_time = ph_get_now_time_msec();
	printf("%ld: Philosopher %d finished.\n", now_time - start_time, philo->id);
	philo->last_eat_time = 0; // replace with actual time function if needed
	return (NULL);
}

void	ph_wait_for_start(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(philo->start_flag->mutex);
		if (philo->start_flag->is_started == true)
		{
			pthread_mutex_unlock(philo->start_flag->mutex);
			break ;
		}
		pthread_mutex_unlock(philo->start_flag->mutex);
		usleep(10);
	}
}
