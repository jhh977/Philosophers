/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:36:35 by jhh               #+#    #+#             */
/*   Updated: 2026/02/04 16:54:06 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dead_process(t_data *data, int i)
{
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n",
		timestamp(data), data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}

int	check_if_dead(t_data *data, int i, long long now)
{
	if (!data->dead
		&& now - data->philos[i].last_meal
		> data->time_to_die)
	{
		data->dead = 1;
		dead_process(data, i);
		return (1);
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
