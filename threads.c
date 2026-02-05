/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:18:08 by jhh               #+#    #+#             */
/*   Updated: 2026/02/04 17:17:52 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void usleep_pattern(t_philo *philo)
{
	if (philo->data->philo_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(1000);
	}
	else
	{
		if (philo->id == philo->data->philo_count - 1)
		{
			usleep(philo->data->time_to_eat * 2000);
		}
		else 
		{
			if (philo->id % 2 == 0 || philo->id == philo->data->philo_count)
				usleep(philo->data->time_to_eat * 1000);
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep_pattern(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
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
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	long long	now;
	int			n;

	data = (t_data *)arg;
	while (1)
	{
		n = 1;
		i = 0;
		while (i < data->philo_count)
		{
			if (data->philos[i].meals_eaten < data->must_eat_count)
				n = 0;
			pthread_mutex_lock(&data->death_mutex);
			now = get_time_ms();
			if(check_if_dead(data, i, now))
				return (NULL);
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		if (n == 1 && data->must_eat_count >= 0)
		{
		    pthread_mutex_lock(&data->death_mutex);
		    data->dead = 1;
		    pthread_mutex_unlock(&data->death_mutex);
			printf("%lld number of meals reached\n",
					timestamp(data));
			return NULL;
		}
		usleep(1000);
	}
	return (NULL);
}

int	single_philo(t_data *data)
{
	print_action(&data->philos[0], "has taken a fork");
	precise_sleep(data->time_to_die, data);
	pthread_mutex_lock(&data->death_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n",
		timestamp(data), data->philos[0].id);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	if (data->philo_count == 1)
		return (single_philo(data));
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL,
			monitor_routine, data) != 0)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
