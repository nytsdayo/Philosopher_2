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

static long	get_now_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	ph_usleep(long time_in_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_now_time();
	while (true)
	{
		current_time = get_now_time();
		if (current_time - start_time >= time_in_ms)
			break ;
		usleep(100);
	}
}
