/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:50:19 by jhijazi           #+#    #+#             */
/*   Updated: 2026/02/06 16:21:29 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	meals_checker(t_data *data, int n)
{
	if (n == 1 && data->must_eat_count >= 0)
	{
		meals_reached(data);
		return (1);
	}
	usleep(900);
	return (0);
}
