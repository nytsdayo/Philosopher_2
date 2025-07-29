/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:49:38 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 16:54:39 by rnakatan         ###   ########.fr       */
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

int	ph_init_dining(t_dining **dining, t_dining_data *data)
{
	int	i;
	int	res;

	*dining = malloc(sizeof(t_dining));
	if (!*dining)
		return (PH_MEMORY_ERROR);
	(*dining)->data = data;
	(*dining)->threads = malloc(sizeof(pthread_t) * data->philo_num);
	(*dining)->forks = malloc(sizeof(t_fork *) * data->philo_num);
	(*dining)->philos = malloc(sizeof(t_philo) * data->philo_num);
	(*dining)->table_info = malloc(sizeof(t_table_info));
	(*dining)->print = malloc(sizeof(t_print));
	if (!(*dining)->threads || !(*dining)->forks || !(*dining)->philos || !(*dining)->table_info || !(*dining)->print)
		return (PH_MEMORY_ERROR);
	(*dining)->table_info->philo_num = data->philo_num;
	res = ph_init_table_info((*dining)->table_info, data->philo_num);
	if (res != PH_SUCCESS)
		return (res);
	res = ph_init_forks((*dining)->forks, data->philo_num);
	if (res != PH_SUCCESS)
		return (res);
	res = ph_init_print((*dining)->print);
	if (res != PH_SUCCESS)
		return (res);
	for (i = 0; i < data -> philo_num; i++)
	{
		(*dining)->philos[i].thread = (*dining)->threads[i];
		(*dining)->philos[i].philo_info = malloc(sizeof(t_philo_info));
		if (!(*dining)->philos[i].philo_info)
			return (PH_MEMORY_ERROR);
		(*dining)->philos[i].philo_info->id = i;
		(*dining)->philos[i].philo_info->left_fork = (*dining)->forks[i];
		(*dining)->philos[i].philo_info->right_fork = (*dining)->forks[(i + 1) % data->philo_num];
		(*dining)->philos[i].philo_info->last_eat_time = 0;
		(*dining)->philos[i].philo_info->start_flag = (*dining)->table_info->start_flag;
		(*dining)->philos[i].philo_info->print_mutex = (*dining)->print;
		(*dining)->philos[i].philo_info->data = data;
		(*dining)->philos[i].table_info = (*dining)->table_info;
	}
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
		forks[i]->mutex = malloc(sizeof(pthread_mutex_t));
		if (!forks[i]->mutex)
			return (PH_MEMORY_ERROR);
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(forks[i]->mutex, NULL) != 0)
		{
			for (int j = 0; j < i; j++)
				pthread_mutex_destroy(forks[j]->mutex);
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
	table_info->start_flag = malloc(sizeof(t_start_flag));
	table_info->start_time = malloc(sizeof(t_start_time));
	
	if (!table_info->start_flag || !table_info->start_time)
		return (PH_MEMORY_ERROR);
	table_info->start_flag->mutex = malloc(sizeof(pthread_mutex_t));
	table_info->start_time->mutex = malloc(sizeof(pthread_mutex_t));
	if (!table_info->start_flag->mutex || !table_info->start_time->mutex)
		return (PH_MEMORY_ERROR);
	if (pthread_mutex_init(table_info->start_flag->mutex, NULL) != 0)
		return (PH_MUTEX_ERROR);
	if (pthread_mutex_init(table_info->start_time->mutex, NULL) != 0)
	{
		pthread_mutex_destroy(table_info->start_flag->mutex);
		return (PH_MUTEX_ERROR);
	}
	table_info->start_flag->is_started = false;
	table_info->start_time->time = 0;
	return (PH_SUCCESS);
}

int	ph_init_print(t_print *print)
{
	print->mutex = malloc(sizeof(pthread_mutex_t));
	if (!print->mutex)
		return (PH_MEMORY_ERROR);
	if (pthread_mutex_init(print->mutex, NULL) != 0)
	{
		return (PH_MUTEX_ERROR);
	}
	return (PH_SUCCESS);
}
