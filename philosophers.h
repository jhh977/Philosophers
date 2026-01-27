/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:43:16 by jhh               #+#    #+#             */
/*   Updated: 2026/01/19 23:24:40 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
typedef struct s_data
{
	int				philo_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	int				dead;
	long long		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int	is_number(char *str);
int	parse_args(int argc, char **argv, t_data *data);
void	init_philos(t_data *data);
int	init_data(t_data *data);
int	ft_atoi(const char *str);
int	start_simulation(t_data *data);
void	cleanup(t_data *data);
long long	get_time_ms(void);
long long	timestamp(t_data *data);

#endif
