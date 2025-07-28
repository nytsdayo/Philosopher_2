/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dining.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 08:32:05 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 00:44:22 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdlib.h>
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	ph_dining(t_dining_data *data)
{
	int			i;
	t_dining	*dining;
	int			ret;

	ret = ph_init_dining(&dining, data);
	if (ret != PH_SUCCESS)
	{
		fprintf(stderr, "Error initializing dining: %d\n", ret);
		if (ret == PH_MEMORY_ERROR)
			fprintf(stderr, "Memory allocation error\n");
		if (dining)
			ph_free_resources(dining);
		return (ret);
	}
	for (i = 0; i < data->philo_num; i++)
		pthread_create(&dining->threads[i], NULL, ph_philo_routine, &dining->philos[i]);
	usleep(1000);
	pthread_mutex_lock(dining->start_flag->mutex);
	dining->start_flag->is_started = true;
	pthread_mutex_unlock(dining->start_flag->mutex);
	for (i = 0; i < data->philo_num; i++)
		pthread_join(dining->threads[i], NULL);
	ph_free_resources(dining);
	return (PH_SUCCESS);
}
