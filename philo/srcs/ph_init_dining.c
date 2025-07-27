/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:49:38 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/15 00:54:20 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <pthread.h>

t_dining	*ph_init_dining(t_dining_data *dining_data)
{
	t_dining	*dining;
	int			i;
	int			ret;

	dining = malloc(sizeof(t_dining) * dining_data->philo_num);
	if (!dining)
	{
		return (NULL);
	}
	i = 0;
	while (i < dining_data->philo_num)
	{
		// must:set thread_function & watasu args
		ret = pthread_create(&dining[i].thread_id, NULL, NULL, NULL);
		if (ret != 0)
		{
			return (NULL);
		}
		i++;
	}
	return (dining);
}
