/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/11 15:40:19 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(int time)
{
	long	start;

	start = my_get_time();
	while (my_get_time() - start < time)
	{
		usleep(25);
	}
}

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
void	*died_check(void *args)
{
	int		i;
	long	now;
	t_phios *philo;
	t_configuration *confg;
	
	philo = (t_phios *)args;
	confg = philo->config;
	while (confg->stop != 1) {
		pthread_mutex_lock(&confg->meal_lock);
		now = my_get_time() - confg->start_time;
		if ((now - philo[i].last_meal) > confg->time_to_die)
		{
			stdout_lock(confg, &philo[i], "is died");
			confg->stop = 1;				
		}		
		pthread_mutex_unlock(&confg->meal_lock);
		i++;
		if(i >= confg->number_of_philosophers)
			i = 0;
		usleep(25);
	}
	return NULL;
}

void	*philo_routine(void *arg)
{
	t_phios	*philo;
	philo = (t_phios *)arg;	
	while (1)
	{
		pthread_mutex_lock(&philo->config->meal_lock);
		if (philo->config->stop)
		{
			pthread_mutex_unlock(&philo->config->meal_lock);
			break;
		}
		pthread_mutex_unlock(&philo->config->meal_lock);
		// start with taking a forks
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		stdout_lock(philo->config, philo, "has taken a fork");
		// for eating
		stdout_lock(philo->config, philo, "is Eating");
		pthread_mutex_lock(&philo->config->meal_lock);
		philo->last_meal = my_get_time() - philo->config->start_time;
		philo->eat_count++;
		pthread_mutex_unlock(&philo->config->meal_lock);
		msleep(philo->config->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		// for sleeping
		stdout_lock(philo->config, philo, "is sleeping");
		msleep(philo->config->time_to_sleep);
		// for thinking
		stdout_lock(philo->config, philo, "is thinking");
		usleep(25);
	}
	return (NULL);
}

void	philo_init(t_configuration *data)
{
	int		i;
	t_phios	*philos;
	pthread_t	died_checker;

	philos = malloc(sizeof(t_phios) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t)
	* data->number_of_philosophers);
	philos->eat_count = 0;
	data->stop = 0;
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
	pthread_create(&died_checker, NULL, died_check, philos);
	join_it(philos);
	pthread_join(died_checker, NULL);
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
