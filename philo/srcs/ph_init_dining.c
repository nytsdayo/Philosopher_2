/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:49:38 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 00:44:33 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

t_fork	*ph_setting_fork(void);

int	ph_init_dining(t_dining **dining, t_dining_data *data)
{
	int	i;

	*dining = malloc(sizeof(t_dining));
	if (!*dining)
		return (PH_MEMORY_ERROR);
	(*dining)->data = data;
	(*dining)->threads = malloc(sizeof(pthread_t) * data->philo_num);
	(*dining)->forks = malloc(sizeof(t_fork) * data->philo_num);
	(*dining)->philos = malloc(sizeof(t_philo) * data->philo_num);
	(*dining)->start_flag = malloc(sizeof(t_start_flag));
	(*dining)->print = malloc(sizeof(t_print));
	if (!(*dining)->threads || !(*dining)->forks || !(*dining)->philos || !(*dining)->start_flag || !(*dining)->print)
		return (PH_MEMORY_ERROR);
	(*dining)->start_flag->mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*dining)->start_flag->mutex)
		return (false);
	(*dining)->start_flag->is_started = false;
	(*dining)->print->mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*dining)->print->mutex)
		return (PH_MEMORY_ERROR);
	for (i = 0; i < data -> philo_num; i++)
	{
		(*dining)->forks[i] = ph_setting_fork();
		if (!(*dining)->forks[i])
			return (PH_MEMORY_ERROR);
		(*dining)->forks[i]->mutex = malloc(sizeof(pthread_mutex_t));
		if (!(*dining)->forks[i]->mutex)
			return (PH_MEMORY_ERROR);
		pthread_mutex_init((*dining)->forks[i]->mutex, NULL);
		(*dining)->forks[i]->is_used = false;
		(*dining)->philos[i].id = i;
		(*dining)->philos[i].data = (*dining)->data;
		(*dining)->philos[i].left_fork = (*dining)->forks[i];
		(*dining)->philos[i].right_fork = (*dining)->forks[(i + 1) % data->philo_num];
		(*dining)->philos[i].last_eat_time = 0;
		(*dining)->philos[i].start_flag = (*dining)->start_flag;
		(*dining)->philos[i].print_mutex = (*dining)->print;
	}
	(*dining)->threads = malloc(sizeof(pthread_t) * data->philo_num);
	pthread_mutex_init((*dining)->start_flag->mutex, NULL);
	pthread_mutex_init((*dining)->print->mutex, NULL);
	return (PH_SUCCESS);
}

t_fork	*ph_setting_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->mutex = malloc(sizeof(pthread_mutex_t));
	if (!fork->mutex)
	{
		free(fork);
		return (NULL);
	}
	if (pthread_mutex_init(fork->mutex, NULL) != 0)
	{
		free(fork->mutex);
		free(fork);
		return (NULL);
	}
	fork->is_used = false;
	return (fork);
}
