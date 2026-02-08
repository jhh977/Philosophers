/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:36:35 by jhh               #+#    #+#             */
/*   Updated: 2026/02/08 15:06:44 by jhijazi          ###   ########.fr       */
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

void	meals_reached(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld number of meals reached\n", timestamp(data));
	pthread_mutex_unlock(&data->print_mutex);
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

void	routine_actions(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->death_mutex);
	take_forks(philo);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "is eating");
	precise_sleep(philo->data->time_to_eat, philo->data);
	put_forks(philo);
	print_action(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep, philo->data);
	if (philo->data->philo_count % 2 != 0)
		usleep(philo->data->time_to_eat * 1000);
	print_action(philo, "is thinking");
}
