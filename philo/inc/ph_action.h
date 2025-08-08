/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:36:28 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/07 22:30:40 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_ACTION_H
# define PH_ACTION_H

# include "ph_dining.h"
# include <stdbool.h>

# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_DEATH "is dead"

int		ph_philo_act(t_philo *philo);
int 	ph_philo_act_eat(t_philo *philo);
void	ph_print_action(t_philo *philo, const char *action);
bool	ph_isdead(t_philo *philo_info);
#endif