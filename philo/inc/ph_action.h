/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:36:28 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 19:09:50 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_ACTION_H
# define PH_ACTION_H

# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"

int		ph_philo_act(t_philo *philo);
int 	ph_philo_act_eat(t_philo *philo);
void	ph_print_action(t_philo *philo, const char *action);
#endif