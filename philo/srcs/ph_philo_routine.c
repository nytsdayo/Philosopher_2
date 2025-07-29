/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:45:19 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 17:19:46 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// static void	ph_wait_for_start(t_philo_info *philo_info);
// static int	ph_philo_eat(t_philo *philo);

void	*ph_philo_routine(void *arg)
{
	t_philo			*philo;
	t_philo_info	*philo_info;
	long	now_time;

	philo = (t_philo *)arg;
	philo_info = philo->philo_info;
	pthread_mutex_lock(philo_info->print_mutex->mutex);
	pthread_mutex_lock(philo->table_info->start_time->mutex);
	now_time = ph_get_now_time_msec();
	printf("%ld: Philosopher %d is eating.\n", now_time - philo->table_info->start_time->time, philo_info->id);
	pthread_mutex_unlock(philo->table_info->start_time->mutex);
	pthread_mutex_unlock(philo_info->print_mutex->mutex);
	ph_usleep(philo_info->data->time_to_eat);
	pthread_mutex_lock(philo_info->print_mutex->mutex);
	now_time = ph_get_now_time_msec();
	printf("%ld: Philosopher %d is sleeping.\n", now_time - philo->table_info->start_time->time, philo_info->id);
	pthread_mutex_unlock(philo_info->print_mutex->mutex);
	ph_usleep(philo_info->data->time_to_sleep);
	pthread_mutex_lock(philo_info->print_mutex->mutex);
	now_time = ph_get_now_time_msec();
	printf("%ld: Philosopher %d is thinking.\n", now_time - philo->table_info->start_time->time, philo_info->id);
	pthread_mutex_unlock(philo_info->print_mutex->mutex);
	philo_info->last_eat_time = now_time - philo->table_info->start_time->time;
	return (NULL);
}

// void	ph_wait_for_start(t_philo_info *philo_info)
// {
// 	while (true)
// 	{
// 		pthread_mutex_lock(philo_info->start_flag->mutex);
// 		if (philo_info->start_flag->is_started)
// 		{
// 			pthread_mutex_unlock(philo_info->start_flag->mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(philo_info->start_flag->mutex);
// 	}
// }

// int		philo_eat(t_philo *philo)
// {
// 	return (ALLIVE);
// }