/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/10 20:06:51 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_it(t_phios *data)
{
	int i;
	
	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
}

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
		pthread_mutex_lock(&philo->config->meal_lock);
		philo->last_meal = my_get_time();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->config->meal_lock);
		usleep(philo->config->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		// for sleeping
		stdout_lock(philo->config, philo, "is sleeping");
		usleep(philo->config->time_to_sleep * 1000);
		// for thinking
		stdout_lock(philo->config, philo, "is thinking");
		usleep(1000);
		if (philo->config->number_of_times_each_philosopher_must_eat <= philo->eat_count)
		{
			stdout_lock(philo->config, philo, "is died");
			exit(0);
		}
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
	philos->eat_count = 1;
	if (!data->forks || !philos)
	{
		t_clean(philos);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->stdout, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	i = 0;
	data->start_time = my_get_time();
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
	join_it(philos);
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
