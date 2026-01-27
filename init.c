/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:57:52 by jhh               #+#    #+#             */
/*   Updated: 2026/01/19 14:58:35 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork
			= &data->forks[(i + 1) % data->philo_count];
		i++;
	}
}


int	init_data(t_data *data)
{
	int	i;

	data->dead = 0;
	data->start_time = get_time_ms();

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (1);

	init_philos(data);
	return (0);
}
