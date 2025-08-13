/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:16 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/13 11:10:16 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_configuration
{
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						stop;
	int						number_of_times_each_philosopher_must_eat;
	long long				start_time;
	long					now;
	pthread_mutex_t			stop_lock;
	pthread_mutex_t			stdout;
	pthread_mutex_t			*forks;
	pthread_mutex_t			meal_lock;
}							t_configuration;

typedef struct s_philos
{
	int						id;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	long long				last_meal;
	int						eat_count;
	long long				start_time;
	struct s_configuration	*config;
}							t_phios;

int							puterror(int errnum);
int							ft_is_all_digit(char *str);
int							philo_parcer(int ac, char **av,
								t_configuration *data);
int							ft_atoi(const char *str);
int							ft_isdigit(int c);
void						t_clean(void *data);
void						stdout_lock(t_configuration *data, t_phios *philo,
								char *str);
long long					my_get_time(void);
#endif