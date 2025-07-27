/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 01:44:07 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/15 04:20:55 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_UTILS_H
# define PH_UTILS_H
# include <stdbool.h>

int		ph_atoi(const char *nptr);
bool	ph_isdigit(char c);
bool	ph_isnum(const char *str);

#endif
