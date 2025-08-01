/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:16 by acennadi          #+#    #+#             */
/*   Updated: 2025/07/30 11:36:43 by acennadi         ###   ########.fr       */
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
	int						number_of_times_each_philosopher_must_eat;
	pthread_mutex_t			stdout;
	pthread_mutex_t			*forks;
}							t_configuration;

typedef struct s_philos
{
	int						id;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	long long				last_meal;
	int						eat_count;
	struct s_configuration	*config;
}							t_phios;

int							puterror(int errnum);
int							ft_is_all_digit(char *str);
int							philo_parcer(int ac, char **av,
								t_configuration *data);
int							ft_atoi(const char *str);
int							ft_isdigit(int c);
void						t_clean(void *arg);
void						stdout_lock(t_configuration *data, t_phios *philo,
								char *str);
long						my_get_time(void);
#endif