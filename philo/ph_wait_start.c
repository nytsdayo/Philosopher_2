/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_wait_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:19:46 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/15 00:19:46 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_mutex.h"

void	ph_wait_start(t_start_time *start_time)
{
	pthread_mutex_lock(&start_time->mutex);
	pthread_mutex_unlock(&start_time->mutex);
}
