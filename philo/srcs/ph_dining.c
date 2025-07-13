/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dining.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 08:32:05 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/13 23:51:10 by rnakatan         ###   ########.fr       */
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

	return (PH_SUCCESS);
}
t_dining_data	*ph_get_dining_data(char **argv)
{
	t_dining_data	*dining_data;

	dining_data = malloc(sizeof(t_dining_data));
	if (!dining_data)
		return (NULL);
	dining_data->philo_num = atoi(argv[1]);
	dining_data->time_to_die = atoi(argv[2]);
	dining_data->time_to_eat = atoi(argv[3]);
	dining_data->time_to_sleep = atoi(argv[4]);
	return (dining_data);
}


