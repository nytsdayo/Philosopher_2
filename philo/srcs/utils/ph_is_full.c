/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_is_full.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdbool.h>

/*
** Checks if a philosopher is "full", meaning they have completed the
** required number of meals. If max_eat_count is not set, this always
** returns false.
*/
bool	ph_philo_is_full(t_philo_info *philo_info)
{
	if (philo_info->philo_data.max_eat_count < 0)
	{
		return (false);
	}
	if (philo_info->eat_count >= philo_info->philo_data.max_eat_count)
	{
		return (true);
	}
	return (false);
}
