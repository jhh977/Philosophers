/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:51:52 by jhijazi           #+#    #+#             */
/*   Updated: 2026/02/05 17:32:36 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitor_helper(t_data *data, int i)
{
	long long	now;

	pthread_mutex_lock(&data->death_mutex);
	now = get_time_ms();
	if (check_if_dead(data, i, now))
		return (1);
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	init_vars(int *n, int *i)
{
	*n = 1;
	*i = 0;
}
