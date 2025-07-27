/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dining.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 08:32:05 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/27 09:32:01 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdlib.h>
#include "ph_status.h"

t_dining_data	*ph_get_dining_data(char **argv);

int	ph_dining(char **argv)
{
	//get dining_data
	// const t_dining_data	dining_data = ph_get_dining_data(argv);
	pthread_t *threads;

	ph_init_dining();
	ph_create_thread();
	i = 0;
	threads = (pthread_t *)malloc(philo_num)
	while(i < philo_num)
	{
		pthread_create(&threads);
		i++;
	}
	i = 0;
	while(i < philo_num)
	{
		pthread_join()
		i++;
	}
	ph_close_dining();
	return (PH_SUCCESS);
}

t_dining_data	*ph_get_dining_data(char **argv)
{
	t_dining_data	*dining_data;

	dining_data = malloc(sizeof(t_dining_data));
	if (!dining_data)
		return (NULL);
	dining_data->philo_num = ph_atoi(argv[1]);
	dining_data->time_to_die = ph_atoi(argv[2]);
	dining_data->time_to_eat = ph_atoi(argv[3]);
	dining_data->time_to_sleep = ph_atoi(argv[4]);
	return (dining_data);
}

int	ph_thread_create()
{
	threads = 
	i = 0;
	while(i < philo_num)
	{
		pthread_create(&threads);
		i++;
	}
}