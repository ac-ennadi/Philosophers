/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/03 17:22:05 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*philo_routine(void *arg)
{
	t_phios	*philo;

	philo = (t_phios *)arg;
	while (1)
	{
		// start with taking a forks
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		stdout_lock(philo->config, philo, "has taken a fork");
		
		// for eating
		stdout_lock(philo->config, philo, "is Eating");
    	philo->last_meal = my_get_time();
		usleep(philo->config->time_to_eat * 1000);
    	philo->eat_count++;
		
		// for sleeping
		stdout_lock(philo->config, philo, "is sleeping");
		usleep(philo->config->time_to_sleep * 1000);
		
		// for thinking
		stdout_lock(philo->config, philo, "is thinking");
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (NULL);
}

void	philo_init(t_configuration *data)
{
	int		i;
	t_phios	*philos;

	philos = malloc(sizeof(t_phios) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks || !philos)
	{
		t_clean(data->forks);
		t_clean(philos);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->stdout, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].config = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philosophers];
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
int	main(int ac, char **av)
{
	int				status;
	t_configuration	data;

	status = philo_parcer(ac, av, &data);
	if (!status)
		return (0);
	philo_init(&data);
	return (0);
}
