/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acennadi <acennadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:25:16 by acennadi          #+#    #+#             */
/*   Updated: 2025/08/13 12:15:03 by acennadi         ###   ########.fr       */
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

void	join_it(t_phios *data, pthread_t died_checker)
{
	int	i;

	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
	pthread_join(died_checker, NULL);
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
		if (data[i].eat_count
			< data->config->number_of_times_each_philosopher_must_eat)
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

void	*died_check(void *args)
{
	int		i;
	t_phios	*philo;

	i = 0;
	philo = (t_phios *)args;
	while (philo->config->stop != 1)
	{
		philo->config->now = my_get_time() - philo->config->start_time;
		pthread_mutex_lock(&philo->config->meal_lock);
		if (((philo->config->now
					- philo[i].last_meal) >= philo->config->time_to_die))
		{
			stdout_lock(philo->config, &philo[i], "is died");
			pthread_mutex_lock(&philo->config->stop_lock);
			philo->config->stop = 1;
			pthread_mutex_unlock(&philo->config->stop_lock);
		}
		pthread_mutex_unlock(&philo->config->meal_lock);
		if (philo->config->number_of_times_each_philosopher_must_eat != -1)
			is_all(philo);
		i++;
		if (i >= philo->config->number_of_philosophers)
			i = 0;
		usleep(25);
	}
	return (NULL);
}
