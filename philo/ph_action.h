/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:36:28 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/16 04:50:55 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_ACTION_H
# define PH_ACTION_H

# include "ph_dining.h"
# include <stdbool.h>

# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_TAKE_FORK "has taken a fork"
# define PHILO_DEATH "died"

int		ph_philo_act(t_philo *philo);
int		ph_philo_act_eat(t_philo *philo);
int		ph_act_usleep(t_philo *philo, long time);
void	ph_print_action(t_philo *philo, const char *action);
bool	ph_isdead(t_philo *philo);
void	ph_release_forks(t_philo_info *philo_info);
void	ph_take_forks(t_philo *philo);

#endif