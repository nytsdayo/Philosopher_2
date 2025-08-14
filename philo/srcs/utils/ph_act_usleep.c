/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_act_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/14 23:08:02 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_action.h"
#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

/*
** A custom usleep function that sleeps for a specified duration ('time')
** while periodically checking if the philosopher has died or if the
** simulation has ended. This makes actions like eating and sleeping
** interruptible.
*/
int	ph_act_usleep(t_philo *philo, long time)
{
	long	start_time;
	long	current_time;

	start_time = ph_get_now_time_msec();
	current_time = start_time;
	while (current_time - start_time < time)
	{
		if (ph_isdead(philo))
		{
			return (PHILO_DEAD);
		}
		if (ph_isexit(philo))
		{
			return (PHILO_EXIT);
		}
		usleep(100);
		current_time = ph_get_now_time_msec();
	}
	return (PHILO_ALIVE);
}
