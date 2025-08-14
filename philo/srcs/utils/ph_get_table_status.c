/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_get_table_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 03:41:42 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/15 03:43:52 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"

int	ph_get_table_status(t_table_status *table_status)
{
	int	value;

	pthread_mutex_lock(&table_status->mutex);
	value = table_status->is_running;
	pthread_mutex_unlock(&table_status->mutex);
	return (value);
}
