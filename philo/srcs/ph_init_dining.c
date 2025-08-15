/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:49:38 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/15 01:20:30 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	ph_init_forks(t_fork **forks, int philo_num);
static int	ph_init_table_info(t_table_info *table_info, int philo_num);
static int	ph_init_print(t_print *print);
static int	ph_malloc_dining(t_dining **dining, t_dining_data data);

/*
** Initializes the main dining structure, including all necessary memory
** allocations and mutex initializations.
*/
int	ph_init_dining(t_dining **dining, t_dining_data data)
{
	int	res;

	if (ph_malloc_dining(dining, data) != PH_SUCCESS)
	{
		return (PH_MEMORY_ERROR);
	}
	res = ph_init_table_info((*dining)->table_info, data.philo_num);
	if (res != PH_SUCCESS)
	{
		return (res);
	}
	res = ph_init_forks((*dining)->forks, data.philo_num);
	if (res != PH_SUCCESS)
	{
		return (res);
	}
	res = ph_init_print((*dining)->print);
	if (res != PH_SUCCESS)
	{
		return (res);
	}
	return (PH_SUCCESS);
}

/*
** Allocates memory for and initializes all forks (mutexes).
*/
static int	ph_init_forks(t_fork **forks, int philo_num)
{
	int	i;
	int	j;

	i = -1;
	while (++i < philo_num)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
			return (PH_MEMORY_ERROR);
	}
	i = -1;
	while (++i < philo_num)
	{
		if (pthread_mutex_init(&forks[i]->mutex, NULL) != 0)
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&forks[j]->mutex);
			return (PH_MUTEX_ERROR);
		}
	}
	return (PH_SUCCESS);
}

/*
** Initializes table-wide information, including status and start time mutexes.
*/
static int	ph_init_table_info(t_table_info *table_info, int philo_num)
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

/*
** Initializes the shared print mutex.
*/
static int	ph_init_print(t_print *print)
{
	if (pthread_mutex_init(&print->mutex, NULL) != 0)
		return (PH_MUTEX_ERROR);
	return (PH_SUCCESS);
}

/*
** Allocates memory for the main dining struct and all its members that
** are pointers.
*/
static int	ph_malloc_dining(t_dining **dining, t_dining_data data)
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
	if (!(*dining)->philo_threads || !(*dining)->forks || !(*dining)->philos
		|| !(*dining)->table_info || !(*dining)->print)
		return (PH_MEMORY_ERROR);
	return (PH_SUCCESS);
}
