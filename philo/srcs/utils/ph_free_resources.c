/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:45:32 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/07 22:01:28 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <pthread.h>
#include <stdlib.h>

void	ph_free_resources(t_dining *dining)
{
	int	i;

	if (!dining)
		return ;
	if (dining->philos)
	{
		for (i = 0; i < dining->data.philo_num; i++)
		{
			if (dining->philos[i]->philo_info)
				free(dining->philos[i]->philo_info);
			free(dining->philos[i]);
		}
		free(dining->philos);
	}
	if (dining->threads)
		free(dining->threads);
	if (dining->forks)
	{
		for (i = 0; i < dining->data.philo_num; i++)
		{
			if (dining->forks[i])
			{
				if (dining->forks[i]->mutex)
				{
					pthread_mutex_destroy(dining->forks[i]->mutex);
					free(dining->forks[i]->mutex);
				}
				free(dining->forks[i]);
			}
		}
		free(dining->forks);
	}
	if (dining->table_info)
	{
		if (dining->table_info->start_time)
		{
			pthread_mutex_destroy(dining->table_info->start_time->mutex);
			free(dining->table_info->start_time->mutex);
			free(dining->table_info->start_time);
		}
		free(dining->table_info);
	}
	if (dining->print)
	{
		if (dining->print->mutex)
		{
			pthread_mutex_destroy(dining->print->mutex);
			free(dining->print->mutex);
		}
		free(dining->print);
	}
	free(dining);
}
