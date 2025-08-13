/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:31:49 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_utils.h"
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

/*
** A more precise version of usleep that takes a duration in milliseconds.
** It uses a loop of smaller usleep calls to avoid oversleeping and to be
** more accurate.
*/
void	ph_usleep(long time_in_ms)
{
	long	start_time;
	long	current_time;

	start_time = ph_get_now_time_msec();
	while (true)
	{
		current_time = ph_get_now_time_msec();
		if (current_time - start_time >= time_in_ms)
		{
			break ;
		}
		usleep(100);
	}
}
