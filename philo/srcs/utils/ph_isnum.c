/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:20:09 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/*
** Checks if a string represents a valid number, allowing for an optional
** leading sign (+ or -).
*/
bool	ph_isnum(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	if (str[i] == '\0')
	{
		return (false);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (false);
		}
		i++;
	}
	return (true);
}
