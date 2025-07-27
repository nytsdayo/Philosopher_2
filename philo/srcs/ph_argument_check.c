/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_argument_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:18:23 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/15 04:48:02 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_status.h"
#include "ph_utils.h"
#include <stdbool.h>
#include <limits.h>

static bool	ph_is_range(int value, int min, int max);

int	ph_argument_check(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (PH_INVAlID_ARGC);
	if (ph_isnum(argv[1]) == false || ph_isnum(argv[2]) == false
		|| ph_isnum(argv[3]) == false || ph_isnum(argv[4]) == false
		|| (argc == 6 && ph_isnum(argv[5]) == false))
		return (PH_INVALID_NOT_NUM);
	if (ph_is_range(ph_atoi(argv[1]), 1, 200) == false
		|| ph_is_range(ph_atoi(argv[2]), 60, INT_MAX)
		|| ph_is_range(ph_atoi(argv[3]), 60, INT_MAX)
		|| ph_is_range(ph_atoi(argv[4]), 60, INT_MAX)
		|| (argc == 6 && ph_is_range(ph_atoi(argv[5]), 0, INT_MAX)))
		return (PH_INVALID_OUT_OF_RANGE);
	return (PH_VAILD_ARG);
}

bool	ph_is_range(int value, int min, int max)
{
	return (value >= min && value <= max);
}
