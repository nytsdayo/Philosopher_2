/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_get_now_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:34:13 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 00:37:18 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

long	ph_get_now_time_msec(void)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (now);
}