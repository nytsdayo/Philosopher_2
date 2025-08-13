/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:45:32 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/14 02:26:43 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <pthread.h>
#include <stdlib.h>

/*
** Frees all allocated resources for the dining simulation, including memory
** for philosophers, forks, threads, and destroys all mutexes.
*/
void	ph_free_resources(t_dining *dining)
{
	int	i;

	if (!dining)
		return ;
	if (dining->philos)
	{
		i = 0;
		while (i < dining->data.philo_num)
		{
			if (dining->philos[i]->philo_info)
				free(dining->philos[i]->philo_info);
			free(dining->philos[i]);
			i++;
		}
		free(dining->philos);
	}
	if (dining->philo_threads)
		free(dining->philo_threads);
	if (dining->forks)
	{
		i = 0;
		while (i < dining->data.philo_num)
		{
			if (dining->forks[i])
			{
				pthread_mutex_destroy(&dining->forks[i]->mutex);
				free(dining->forks[i]);
			}
			i++;
		}
		free(dining->forks);
	}
	if (dining->table_info)
	{
		if (dining->table_info->start_time)
		{
			pthread_mutex_destroy(&dining->table_info->start_time->mutex);
			free(dining->table_info->start_time);
		}
		free(dining->table_info);
	}
	if (dining->print)
	{
		pthread_mutex_destroy(&dining->print->mutex);
		free(dining->print);
	}
	free(dining);
}
