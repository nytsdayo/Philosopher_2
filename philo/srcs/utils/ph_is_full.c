/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_is_full.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:01:59 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 20:01:59 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include <stdbool.h>

bool	ph_philo_is_full(t_philo_info *philo_info)
{
	if (philo_info->philo_data.max_eat_count < 0)
		return (false);
	if (philo_info->eat_count >= philo_info->philo_data.max_eat_count)
		return (true);
	return (false);
}
