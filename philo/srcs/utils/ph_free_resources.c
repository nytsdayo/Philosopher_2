/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:45:32 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 00:54:06 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <pthread.h>
#include <stdlib.h>

void	ph_free_resources(t_dining *dining)
{
	int	i;

	if (!dining)
		return;
	if (dining->threads)
	{
		free(dining->threads);
	}
	if (dining->forks)
	{
		for (i = 0; i < dining->data->philo_num; i++)
		{
			if (dining->forks[i]->mutex)
			{
				pthread_mutex_destroy(dining->forks[i]->mutex);
				free(dining->forks[i]->mutex);
			}
		}
		free(dining->forks);
	}
	if (dining->philos)
		free(dining->philos);
	if (dining->start_flag)
	{
		if (dining->start_flag->mutex)
		{
			pthread_mutex_destroy(dining->start_flag->mutex);
			free(dining->start_flag->mutex);
		}
		free(dining->start_flag);
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
	free(dining->data);
	free(dining);
}
