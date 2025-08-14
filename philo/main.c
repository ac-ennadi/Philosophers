/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/14 10:48:20 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo(t_phios *philos, t_configuration *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks || !philos)
	{
		t_clean(philos);
		t_clean(data->forks);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i].eat_count = 0;
		philos[i].last_meal = 0;
		i++;
	}
	pthread_mutex_init(&data->stdout, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->stop_lock, NULL);
	i = 0;
	data->stop = 0;
	data->i = 0;
	data->start_time = my_get_time();
}

void	in_routine(t_phios *philo)
{
	pthread_mutex_lock(philo->right_fork);
	stdout_lock(philo->config, philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	stdout_lock(philo->config, philo, "has taken a fork");
	pthread_mutex_lock(&philo->config->meal_lock);
	philo->last_meal = my_get_time() - philo->start_time;
	philo->eat_count++;
	pthread_mutex_unlock(&philo->config->meal_lock);
	stdout_lock(philo->config, philo, "is Eating");
	msleep(philo->config->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	stdout_lock(philo->config, philo, "is sleeping");
	msleep(philo->config->time_to_sleep);
	stdout_lock(philo->config, philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_phios	*philo;

	philo = (t_phios *)arg;
	if (philo->id % 2 == 0)
		usleep(250);
	while (1)
	{
		pthread_mutex_lock(&philo->config->stop_lock);
		if (philo->config->stop == 1)
		{
			pthread_mutex_unlock(&philo->config->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->config->stop_lock);
		in_routine(philo);
	}
	return (NULL);
}

void	philo_init(t_configuration *data)
{
	int			i;
	t_phios		*philos;
	pthread_t	died_checker;

	philos = malloc(sizeof(t_phios) * (data->number_of_philosophers));
	set_philo(philos, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].config = data;
		philos[i].start_time = philos[i].config->start_time;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philosophers];
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_create(&died_checker, NULL, died_check, philos);
	join_it(philos, died_checker);
	t_clean(philos);
	t_clean(data->forks);
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
