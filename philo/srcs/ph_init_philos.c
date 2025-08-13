/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <stdlib.h>

static int			ph_init_philo(t_philo **philo_ptr, int id, t_dining *dining,
						t_philo_data philo_data);
static t_philo_data	ph_get_philo_data(t_dining_data data);

/*
** Initializes all philosopher structures in a loop.
*/
int	ph_init_philos(t_philo ***philos_ptr, t_dining *dining)
{
	int				i;
	t_philo_data	philo_data;
	int				ret;

	i = 0;
	philo_data = ph_get_philo_data(dining->data);
	while (i < dining->data.philo_num)
	{
		ret = ph_init_philo(&(*philos_ptr)[i], i + 1, dining, philo_data);
		if (ret != PH_SUCCESS)
			return (ret);
		i++;
	}
	return (PH_SUCCESS);
}

/*
** Creates a t_philo_data struct from the main t_dining_data.
** This is used to pass a subset of the data to each philosopher.
*/
static t_philo_data	ph_get_philo_data(t_dining_data data)
{
	t_philo_data	philo_data;

	philo_data.time_to_die = data.time_to_die;
	philo_data.time_to_eat = data.time_to_eat;
	philo_data.time_to_sleep = data.time_to_sleep;
	philo_data.max_eat_count = data.max_eat_count;
	return (philo_data);
}

/*
** Initializes a single philosopher structure, including its personal info,
** mutexes, and fork assignments.
*/
static int	ph_init_philo(t_philo **philo_ptr, int id, t_dining *dining,
		t_philo_data philo_data)
{
	(*philo_ptr) = malloc(sizeof(t_philo));
	if (!(*philo_ptr))
		return (PH_MEMORY_ERROR);
	(*philo_ptr)->philo_info = malloc(sizeof(t_philo_info));
	if (!(*philo_ptr)->philo_info)
		return (PH_MEMORY_ERROR);
	(*philo_ptr)->philo_info->id = id;
	(*philo_ptr)->table_info = dining->table_info;
	(*philo_ptr)->philo_info->left_fork = dining->forks[id - 1];
	(*philo_ptr)->philo_info->right_fork = dining->forks[id
		% dining->data.philo_num];
	(*philo_ptr)->philo_info->last_eat_time = 0;
	(*philo_ptr)->philo_info->print_mutex = dining->print;
	(*philo_ptr)->philo_info->eat_count = 0;
	if (pthread_mutex_init(&(*philo_ptr)->philo_info->last_eat_time_mutex,
			NULL) != 0)
		return (PH_MUTEX_ERROR);
	(*philo_ptr)->philo_info->is_alive = malloc(sizeof(t_philo_alive));
	if (!(*philo_ptr)->philo_info->is_alive)
		return (PH_MEMORY_ERROR);
	if (pthread_mutex_init(&(*philo_ptr)->philo_info->is_alive->mutex,
			NULL) != 0)
		return (PH_MUTEX_ERROR);
	(*philo_ptr)->philo_info->is_alive->value = true;
	(*philo_ptr)->philo_info->philo_data = philo_data;
	return (PH_SUCCESS);
}
