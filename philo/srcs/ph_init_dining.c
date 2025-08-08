/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:49:38 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 12:54:41 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static int	ph_init_forks(t_fork **forks, int philo_num);
static int	ph_init_table_info(t_table_info *table_info, int philo_num);
static int	ph_init_print(t_print *print);
static int	ph_malloc_dining(t_dining **dining, t_dining_data data);

int	ph_init_dining(t_dining **dining, t_dining_data data)
{
	int	res;

	if (ph_malloc_dining(dining, data) != PH_SUCCESS)
		return (PH_MEMORY_ERROR);
	res = ph_init_table_info((*dining)->table_info, data.philo_num);
	if (res != PH_SUCCESS)
		return (res);
	res = ph_init_forks((*dining)->forks, data.philo_num);
	if (res != PH_SUCCESS)
		return (res);
	res = ph_init_print((*dining)->print);
	if (res != PH_SUCCESS)
		return (res);
	return (PH_SUCCESS);
}

int	ph_init_forks(t_fork **forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
			return (PH_MEMORY_ERROR);
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(&forks[i]->mutex, NULL) != 0)
		{
			for (int j = 0; j < i; j++)
				pthread_mutex_destroy(&forks[j]->mutex);
			return (PH_MUTEX_ERROR);
		}
		forks[i]->is_used = false;
		i++;
	}
	return (PH_SUCCESS);
}

int	ph_init_table_info(t_table_info *table_info, int philo_num)
{
	table_info->philo_num = philo_num;
	table_info->start_time = malloc(sizeof(t_start_time));
	if (!table_info->start_time)
		return (PH_MEMORY_ERROR);
	if (pthread_mutex_init(&table_info->start_time->mutex, NULL) != 0)
		return (PH_MUTEX_ERROR);
	table_info->start_time->time = 0;
	table_info->status.is_running = true;
	if (pthread_mutex_init(&table_info->status.mutex, NULL) != 0)
		return (PH_MUTEX_ERROR);
	return (PH_SUCCESS);
}

int	ph_init_print(t_print *print)
{
	if (pthread_mutex_init(&print->mutex, NULL) != 0)
		return (PH_MUTEX_ERROR);
	return (PH_SUCCESS);
}

int ph_malloc_dining(t_dining **dining, t_dining_data data)
{
	*dining = malloc(sizeof(t_dining));
	if (!*dining)
		return (PH_MEMORY_ERROR);
	(*dining)->data = data;
	(*dining)->philo_threads = malloc(sizeof(pthread_t) * data.philo_num);
	(*dining)->forks = malloc(sizeof(t_fork *) * data.philo_num);
	(*dining)->philos = malloc(sizeof(t_philo *) * data.philo_num);
	(*dining)->table_info = malloc(sizeof(t_table_info));
	(*dining)->print = malloc(sizeof(t_print));
	if ((*dining)->philo_threads == NULL
		|| (*dining)->forks == NULL || (*dining)->philos == NULL
		|| (*dining)->table_info == NULL || (*dining)->print == NULL)
		return (PH_MEMORY_ERROR);
	return (PH_SUCCESS);
}
