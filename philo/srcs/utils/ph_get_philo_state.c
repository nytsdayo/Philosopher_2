/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_get_philo_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:20:47 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/15 02:36:02 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"

int	ph_get_philo_state(t_philo_state *philo_state)
{
	int	value;

	pthread_mutex_lock(&philo_state->mutex);
	value = philo_state->value;
	pthread_mutex_unlock(&philo_state->mutex);
	return (value);
}
