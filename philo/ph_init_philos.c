/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:37:19 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:37:25 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <stdlib.h>

static int			ph_init_philo(t_philo **philo_ptr, int id, t_dining *dining,
						t_philo_data philo_data);
static t_philo_data	ph_get_philo_data(t_dining_data data);
static int			ph_set_philo_info(
						t_philo_info *philo_info,
						int id,
						t_dining *dining,
						t_philo_data philo_data
						);

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
static int	ph_init_philo(
		t_philo **philo_ptr,
		int id,
		t_dining *dining,
		t_philo_data philo_data)
{
	int	ret;

	(*philo_ptr) = malloc(sizeof(t_philo));
	if (!(*philo_ptr))
		return (PH_MEMORY_ERROR);
	(*philo_ptr)->philo_info = malloc(sizeof(t_philo_info));
	if (!(*philo_ptr)->philo_info)
		return (PH_MEMORY_ERROR);
	(*philo_ptr)->table_info = dining->table_info;
	ret = ph_set_philo_info((*philo_ptr)->philo_info, id, dining, philo_data);
	return (ret);
}

static int	ph_set_philo_info(
		t_philo_info *philo_info,
		int id,
		t_dining *dining,
		t_philo_data philo_data)
{
	philo_info->id = id;
	philo_info->left_fork = dining->forks[id - 1];
	philo_info->right_fork = dining->forks[id % dining->data.philo_num];
	philo_info->last_eat_time = 0;
	philo_info->print_mutex = dining->print;
	if (pthread_mutex_init(&philo_info->eat_count.mutex,
			NULL) != 0)
		return (PH_MUTEX_ERROR);
	philo_info->eat_count.value = 0;
	if (pthread_mutex_init(&philo_info->state.mutex,
			NULL) != 0)
	{
		pthread_mutex_destroy(&philo_info->eat_count.mutex);
		return (PH_MUTEX_ERROR);
	}
	philo_info->state.value = PHILO_ALIVE;
	philo_info->philo_data = philo_data;
	return (PH_SET_SUCESS);
}
