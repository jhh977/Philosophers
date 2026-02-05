/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:43:16 by jhh               #+#    #+#             */
/*   Updated: 2026/02/05 17:31:57 by jhijazi          ###   ########.fr       */
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

int			is_number(char *str);
int			parse_args(int argc, char **argv, t_data *data);
void		init_philos(t_data *data);
int			init_data(t_data *data);
int			ft_atoi(const char *str);
int			start_simulation(t_data *data);
void		cleanup(t_data *data);
long long	get_time_ms(void);
long long	timestamp(t_data *data);
void		dead_process(t_data *data, int i);
void		print_action(t_philo *philo, char *msg);
void		precise_sleep(long long ms, t_data *data);
void		take_forks(t_philo *philo);
void		put_forks(t_philo *philo);
int			check_if_dead(t_data *data, int i, long long now);
void		meals_reached(t_data *data);
int			monitor_helper(t_data *data, int i);
void		init_vars(int *n, int *i);
void		routine_actions(t_philo *philo);

#endif
