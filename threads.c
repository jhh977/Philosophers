/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:18:08 by jhh               #+#    #+#             */
/*   Updated: 2026/01/20 17:15:35 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	time = timestamp(philo->data);
	printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	precise_sleep(long long ms, t_data *data)
{
	long long	start;

	start = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		if (get_time_ms() - start >= ms)
			return ;
		usleep(500);
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);

		print_action(philo, "is thinking");
		take_forks(philo);

		pthread_mutex_lock(&philo->data->death_mutex);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->data->death_mutex);

		print_action(philo, "is eating");
		precise_sleep(philo->data->time_to_eat, philo->data);

		put_forks(philo);

		print_action(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	long long	now;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&data->death_mutex);
			now = get_time_ms();
			if (!data->dead
				&& now - data->philos[i].last_meal
				> data->time_to_die)
			{
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("%lld %d died\n",
					timestamp(data), data->philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
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

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long long	timestamp(t_data *data)
{
	return (get_time_ms() - data->start_time);
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
