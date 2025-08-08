/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:31:49 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/07 21:53:54 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include "ph_utils.h"

void	ph_usleep(long time_in_ms)
{
	long	start_time;
	long	current_time;

	start_time = ph_get_now_time_msec();
	while (true)
	{
		current_time = ph_get_now_time_msec();
		if (current_time - start_time >= time_in_ms)
			break ;
		usleep(100);
	}
}
