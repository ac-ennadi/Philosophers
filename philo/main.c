/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:20 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/12 11:25:42 by acennadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(long time)
{
	long	start;

	start = my_get_time();
	while ((my_get_time() - start) < time)
	{
		usleep(25);
	}
}

void	is_all(t_phios *data)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	while (i < data->config->number_of_philosophers)
	{
		pthread_mutex_lock(&data[i].config->meal_lock);
		if (data[i].eat_count < data->config->number_of_times_each_philosopher_must_eat)
		{
			done = 0;
			pthread_mutex_unlock(&data[i].config->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data[i].config->meal_lock);
		i++;
	}
	if (done)
	{
		pthread_mutex_lock(&data->config->stop_lock);
		data->config->stop = 1;
		pthread_mutex_unlock(&data->config->stop_lock);
	}
}

void	join_it(t_phios *data)
{
	int	i;

	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
}

void	*died_check(void *args)
{
	int				i;
	long			now;
	t_phios			*philo;
	t_configuration	*confg;

	i = 0;
	philo = (t_phios *)args;
	confg = philo->config;
	while (confg->stop != 1)
	{
		now = my_get_time() - confg->start_time;
		pthread_mutex_lock(&confg->meal_lock);
		if (((now - philo[i].last_meal) >= confg->time_to_die))
		{
			stdout_lock(confg, &philo[i], "is died");
			pthread_mutex_lock(&philo->config->stop_lock);
			confg->stop = 1;
			pthread_mutex_unlock(&philo->config->stop_lock);
		}
		pthread_mutex_unlock(&confg->meal_lock);
		if (philo->config->number_of_times_each_philosopher_must_eat != -1)
			is_all(philo);
		i++;
		if (i >= confg->number_of_philosophers)
			i = 0;
		usleep(25);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phios	*philo;

	philo = (t_phios *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->config->stop_lock);
		if (philo->config->stop == 1)
		{
			pthread_mutex_unlock(&philo->config->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->config->stop_lock);
		// start with taking a forks
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
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
	}
	return (NULL);
}

void	philo_init(t_configuration *data)
{
	int			i;
	t_phios		*philos;
	pthread_t	died_checker;

	philos = malloc(sizeof(t_phios) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	data->stop = 0;
	if (!data->forks || !philos)
	{
    t_clean(data->forks);
		t_clean(philos);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i].eat_count = 0;
		i++;
	}
	pthread_mutex_init(&data->stdout, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->stop_lock, NULL);
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
  t_clean(data->forks);
  t_clean(philos);
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
